#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>

class OpenGL {
	private:
	unsigned int VBO;

	unsigned int shaderProgram;

	unsigned int VAO;

	unsigned int EBO;

	bool wireframe;
	
	public:
	OpenGL(GLFWwindow* window);

	void GLRender();
};