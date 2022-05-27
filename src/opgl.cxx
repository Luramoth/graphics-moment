#include "include/opgl.hxx"
#include "include/colormod.hxx"

#include <GLFW/glfw3.h>
#include <cstddef>
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
const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

// some vertex data that draws a triangle
float vertices[] = {
	0.5f,	0.5f,	0.0f,  // top right
	0.5f,	-0.5f,	0.0f,  // bottom right
	-0.5f,	-0.5f,	0.0f,  // bottom left
	-0.5f,	0.5f,	0.0f   // top left 
};

unsigned int indices[] = {  // note that we start from 0!
	0,	1,	3,   // first triangle
	1,	2,	3    // second triangle
};  

// set wether or not to see wireframe view
bool wireframe = true;

OpenGL::OpenGL(GLFWwindow* window){
	std::cout << magenta << "initialising OpenGL\n";

	//VBO Vertex Buffer Object, this generates a buffer with a unique ID
	glGenBuffers(1 , &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// bind the buffer to an array

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// set the buffer data to the vertices as defined earlier

	// assign the vertex shader to actually be the vertex shader for OpenGl
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// grab the vertex shader source and compile it
	glShaderSource(vertexShader, 1 , &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	// check and see if the compilation was successful 
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED " << infoLog << std::endl;
	}

	// grab the fragment shader source and compile it
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create a shader program that links all the shaders together
	shaderProgram = glCreateProgram();

	// attach shaders to shader program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// check if thins actually worked
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success){
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER_PROGRAM::LINKING_FAILED " << infoLog << std::endl;
	}

	//actually use the program
	glUseProgram(shaderProgram);

	//delete shaders as we dont need them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//tell OpenGL how to handle these vertices

	//size of vert attribute-|  |-type of attribute| the space between attributes| offset data
	//where the vertex is-v  v  v normalize data?v         v               v------------|
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//create a vertex array object
	glGenVertexArrays(1, &VAO);


	// creat a Element Buffer Object
	glGenBuffers(1, &EBO);

	// gotta copy them indicies
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	//::initialise everything::
	//bind Vertex Array Object
	glBindVertexArray(VAO);

	//copy vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//copy index array in a element  buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// checks if user is in wireframe view
	if (wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void OpenGL::GLRender(){
	// draw the triangle
	glUseProgram(shaderProgram);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}