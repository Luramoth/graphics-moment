#include "include/opgl.hxx"
#include "include/colormod.hxx"

#include <GLFW/glfw3.h>
#include <iostream>

Color::Modifier magenta(Color::FG_MAGENTA);

//vertex shader source code (GLSL)
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

// fragment shader source code (GLSL)
const char *fragmentShaderSource = "#version 330 core"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

// some vertex data that draws a triangle
float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

void OpenGL::init(GLFWwindow* window){
	std::cout << magenta << "initialising OpenGL\n";

	//VBO Vertex Buffer Object, this generates a buffer with a unique ID
	unsigned int VBO;
	glGenBuffers(1 , &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// bind the buffer to an array

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// set the buffer data to the vertices as defined earlier

	// assign the vertex shader to actually be the vertex shader for OpenGl
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// grab the shader source and compile it
	glShaderSource(vertexShader, 1 , &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
}