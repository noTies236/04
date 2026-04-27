// Lib
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
//#include <glfw3.h>
#include "../../../../../../../../../../../../../../Users/wallyson/lib/glfw-3.4/glfw-3.4/include/GLFW/glfw3.h"
#include <vector>

// Headers
#include "Pipeline/Pipeline.h"

int main() 
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, "04", NULL, NULL);

	if (!window) {
		std::cout << "windows not created\n";
	}
	
	glfwMakeContextCurrent(window);

	if (gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD has been inicialized!!! I'm glad :-)" << std::endl;
	} else {
		std::cout << "Falha ao inicializar GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	Pipeline::ImageBuffer::loadImage("C:/Users/wallyson/Downloads/img-1023083-flash.jpg", Pipeline::ImageBuffer::texture);
	
	Pipeline::PreDraw();
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Pipeline::Draw();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 1;
}