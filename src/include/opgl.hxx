#pragma once

#include "glad/glad.h"
#include "shader.hxx"

#include <GLFW/glfw3.h>

class VAO{
	private:
	GLuint id;

	public:
	VAO() {
		glGenVertexArrays(1, &id);
	}

	~VAO(){
		glDeleteVertexArrays(1, &id);
	}

	void bind() {
		glBindVertexArray(id);
	}
};

class OpenGL {
	private:
	VAO vao;

	unsigned int VBO;

	unsigned int shaderProgram;

	unsigned int EBO;

	Shader baseShaders{"src/shaders/vertex.glsl","src/shaders/fragment.glsl"};
	
	public:
	OpenGL(GLFWwindow* window);

	bool wireframe;

	void GLRender();
};

//Vertex Array Object