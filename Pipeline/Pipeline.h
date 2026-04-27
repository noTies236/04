#include <glad/glad.h>
#include "../stb_image.h"

namespace Pipeline {
	extern GLuint gProgramPipeline;
	std::string LoadShaderAsString(const std::string& fileName);
	void		VertexSpecification();
	GLuint		CompileShaderProgram(GLuint type, const std::string& source);
	GLuint		CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
	void		GraphcisPipiline();
	void        PreDraw();
	void        Draw();
	
	namespace ImageBuffer {
		extern GLuint texture;
		void loadImage(const std::string& fileName, GLuint& texture);
		void debug();
	}

	namespace Debug {
		void error();
	}
}