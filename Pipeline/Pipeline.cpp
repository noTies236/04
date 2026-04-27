// Libs
#include "iostream"
#include "fstream"
#include "vector"
#include "string"
#include <array>

// Headers
#include "Pipeline.h"

// Global
GLuint VAO;
GLuint VBO;
//GLuint colorVBO;

// Shader program
GLuint gVertex;
GLuint gFragment;

// Program
//GLuint gProgramPipeline = 0;
GLuint Pipeline::gProgramPipeline = 0;
GLuint Pipeline::ImageBuffer::texture = 0;

namespace Pipeline {

    // Função para carregar o shader a partir de um arquivo
    std::string LoadShaderAsString(const std::string& fileName)
    {
        //std::cout << fileName;

        std::string result = "";
        std::string line = "";
        std::ifstream myFile(fileName.c_str());

        if (myFile.is_open()) {
            while (std::getline(myFile, line)) {
                result += line + "\n";
            }

            myFile.close();
        }

        return result;
    }

    // Função para configurar a geometria do triângulo
    void VertexSpecification()
    {
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        struct Vertex {
            float position[3];   
            float normal[3];     // nx, ny, nz
            float texCoord[2];   // u, v
        };

       /* std::vector<Vertex> houseVertices {
            { {0.5f, 1.0f, 2.0f}, { 0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f} },
            { { -0.5f, 0.0f, 2.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f} },
            { { 0.0f, 1.0f , 2.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f} },
		};*/

		/*std::vector<float> houseVertices {
             0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.8f, 0.0f,
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 7.0f,
             1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  0.4f, 1.0f
		};*/

        Vertex houseVertices[] {
            { {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f}, { 0.5f, 1.0f} },
            { { -1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f} },
            { { 1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f} }
		};

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(houseVertices), houseVertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (void*)0);
		
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 3));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 8, (GLvoid*)(sizeof(GL_FLOAT) * 6));

        glBindVertexArray(0);
        Pipeline::Debug::error();
    }

    // Função para compilar o shader
    GLuint CompileShaderProgram(GLuint type, const std::string& source)
    {
        GLuint shaderObject = glCreateShader(type); // Corrigido para usar o tipo correto

        const char* src = source.c_str();
        glShaderSource(shaderObject, 1, &src, nullptr);
        glCompileShader(shaderObject);

        int success;
        char infoLog[512];
        glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
            std::cout << "Erro na compilação do shader: " << infoLog << std::endl;
        }
        Pipeline::Debug::error();

        return shaderObject;
    }

    // Função para criar o programa de shader
    GLuint CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
    {
        GLuint programObject = glCreateProgram();

        GLuint myVertexShader = CompileShaderProgram(GL_VERTEX_SHADER, vertexSource); // Corrigido para GL_VERTEX_SHADER
        GLuint myFragmentShader = CompileShaderProgram(GL_FRAGMENT_SHADER, fragmentSource); // Corrigido para GL_FRAGMENT_SHADER

        glAttachShader(programObject, myVertexShader);
        glAttachShader(programObject, myFragmentShader);
        glLinkProgram(programObject);
        Pipeline::Debug::error();

        return programObject;
    }

    // Função para configurar o pipeline gráfico
    void GraphicsPipeline()
    {
        std::string vertexShaderSource = LoadShaderAsString("./Shaders/OpenGL/vert.glsl");
        std::string fragmentShaderSource = LoadShaderAsString("./Shaders/OpenGL/frag.glsl");

        Pipeline::gProgramPipeline = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
    }

    void PreDraw()
    {
        //glDisable(GL_DEPTH_TEST);
        //glDisable(GL_CULL_FACE);

        //glViewport(0, 0, 640, 480);
        //glClearColor(0.f, 1.f, 1.f, 1.f);
        //glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        //glUseProgram(Pipeline::gProgramPipeline);
        VertexSpecification();
        GraphicsPipeline();

    }

    void Draw()
    {
        glBindVertexArray(VAO);
        glUseProgram(Pipeline::gProgramPipeline); // Ativar o shader antes de desenhar
        glBindTexture(GL_TEXTURE_2D, Pipeline::ImageBuffer::texture);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

     namespace ImageBuffer {
        void loadImage(const std::string& fileName, GLuint& texture)
        {
            // back in here: i wanna know why do i have to pass &texture into glGenTexture
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            int width, height, channels;

            stbi_set_flip_vertically_on_load(true);
            unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channels, 0);

            if (data) {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else {
                std::cout << "Failed to load texture" << std::endl;
            }
            
			stbi_image_free(data);
        }
	 }

    namespace Debug
    {
        void error()
		{
            GLenum err;

            while ((err = glGetError()) != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << err << std::endl;
            }
        }
    }
}


