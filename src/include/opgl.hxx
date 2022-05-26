#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class OpenGL {
	private:

	unsigned int shaderProgram;

	unsigned int VAO;
	
	public:
	
	OpenGL(GLFWwindow* window);

	void GLRender();
};