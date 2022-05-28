#include "include/opgl.hxx"
#include "include/colormod.hxx"
#include "include/shader.hxx"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

Color::Modifier magenta(Color::FG_MAGENTA);

/* //vertex shader source code (GLSL)
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
	"}\0"; */

// some vertex data that draws a triangle
float vertices[] = {
	// positions			// colors
	0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	0.0f,   // bottom right
	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,   // bottom left
	0.0f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f    // top 
};

unsigned int indices[] = {  // note that we start from 0!
	0,	1,	3,   // first triangle
	1,	2,	3    // second triangle
};  

// set wether or not to see wireframe view
bool wireframe = true;



OpenGL::OpenGL(GLFWwindow* window){
	/* std::cout << magenta << "initialising OpenGL\n";

	//VBO Vertex Buffer Object, this generates a buffer with a unique ID
	glGenBuffers(1 , &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);// bind the buffer to an array

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// set the buffer data to the vertices as defined earlier

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
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);


	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1); */

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);
}

void OpenGL::GLRender(){
	/* // checks if user is in wireframe view
	if (wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	} */

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render the triangle
	baseShaders.use();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}