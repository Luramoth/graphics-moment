#pragma once

#include "glad/glad.h"
#include "shader.hxx"

#include <GLFW/glfw3.h>

class OpenGL {
	private:
	unsigned int VBO;

	unsigned int shaderProgram;

	unsigned int VAO;

	unsigned int EBO;
	
	public:
	OpenGL(GLFWwindow* window);

	bool wireframe;

	void GLRender();
};