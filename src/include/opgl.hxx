#pragma once

#include "glad/glad.h"
#include "shader.hxx"
#include "texture.hxx"

#include <GLFW/glfw3.h>
#include <cstddef>

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

// element array buffer that connects all the polygons and all that
class EBO {
	private:
	GLuint id;

	public:
	EBO() {
		glGenBuffers(1, &id);
	}

	~EBO() {
		glDeleteBuffers(1, &id);
	}

	void bind() {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void upload_data(size_t size, unsigned int *indices) {
		this ->bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}
};

class OpenGL {
	private:
	VAO vao;

	VBO vbo;

	unsigned int shaderProgram;

	EBO ebo;

	Texture tex{"src/images/testpic.png", GL_RGB};
	Texture tex2{"src/images/awesomeface.png", GL_RGBA};

	Shader baseShaders{"src/shaders/vertex.glsl","src/shaders/fragment.glsl"};
	
	public:
	OpenGL(GLFWwindow* window);

	bool wireframe;

	void GLRender();
};

//Vertex Array Object