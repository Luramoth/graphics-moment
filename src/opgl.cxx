#include "include/opgl.hxx"
#include "include/colormod.hxx"
#include "include/shader.hxx"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

Color::Modifier magenta(Color::FG_MAGENTA);

// some vertex data that draws a triangle
float vertices[] = {
	// positions			// colors
	0.5f,	0.5f,	0.0f,	1.0f,	0.0f,	1.0f,	// top right
	0.5f,	-0.5f,	0.0f,	1.0f,	0.0f,	0.0f,	// bottom right
	-0.5f,	-0.5f,	0.0f,	0.0f,	1.0f,	0.0f,	// bottom left
	-0.5f,	0.5f,	0.0f,	0.0f,	0.0f,	1.0f	// top left
};

unsigned int indices[] = {  // note that we start from 0!
	0,	1,	3,   // first triangle
	1,	2,	3    // second triangle
};

float texCords[] = {
	0.0f,	0.0f,	//lower left corner
	1.0f,	0.0f,	//lower right corner
	0.05f,	1.0f	//top center corner
};

// set wether or not to see wireframe view
bool wireframe = true;

OpenGL::OpenGL(GLFWwindow* window){
	std::cout << magenta << "initialising OpenGL\n";

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    vao.bind();

	vbo.bind();

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ebo.bind(indices, sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

	///texture shit///

	// texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	float boarderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, boarderColor);

	// texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// mipmaps
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void OpenGL::GLRender(){
	// checks if user is in wireframe view
	if (wireframe){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// render the triangle
	baseShaders.use();
	vao.bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}