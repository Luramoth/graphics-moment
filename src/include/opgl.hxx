#pragma once

#include "glad/glad.h"
#include "shader.hxx"

#include <GLFW/glfw3.h>

// Vertex Array Object, this contains the constructors and destructors to make the vertex array
class VAO {
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

// Vertex Buffer Object contains all the constructors and destructors to make vertex buffers
class VBO {
	private:
	GLuint id;

	public:
	VBO() {
		glGenBuffers(1, &id);
	}

	~VBO() {
		glDeleteBuffers(1, &id);
	}

	void bind() {
		glBindBuffer(GL_ARRAY_BUFFER ,id);
	}
};

class OpenGL {
	private:
	VAO vao;

	VBO vbo;

	unsigned int shaderProgram;

	unsigned int EBO;

	Shader baseShaders{"src/shaders/vertex.glsl","src/shaders/fragment.glsl"};
	
	public:
	OpenGL(GLFWwindow* window);

	bool wireframe;

	void GLRender();
};

//Vertex Array Object