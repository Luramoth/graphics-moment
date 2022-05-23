#include "include/app.hxx"
#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// simple vertex shader
const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

void Application::run(){
	initWindow();
	mainloop();
	cleanup();
}

void Application::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);// tell GLFW what version of opengl we are using, the major an minor details are structured like this:
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);// [glfw major].[glfw minor] so in this case i am using opengl 3.3

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// tell GLFW what opengl function i want to use, here im using core because thats where all the modern stuff is

	window = glfwCreateWindow(WIDTH, HEIGHT, "graphics moment", NULL, NULL);// actually create the window (yay)

	if (window == NULL){
		std::cerr << "failed to create window\n";// quickly check and see if the window did in fact open
	}

	glfwMakeContextCurrent(window);// tell glfw "no really, we want to render to this window"

	glViewport(0,0, 800, 600);

	// make the window a nice and pretty, subtle color of a really agressive magenta
	// why magenta? because if the main loop doesent work at all its at least aggressively shown to the user that somthing is very clearly wrong
	glClearColor(1.0f,0.0f,1.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	glfwSwapBuffers(window);

	std::cout << "project initialised!\n";
}

void Application::mainloop(){
	std::cout << "running main loop\n";

	std::cout << "compilation test\n";

	float verticies[] = {// vertex data for opengl
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int VBO;// Vertext Buffer Objects variable is a packet of information to be sent to the GPU
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);// send that data off the the GPU

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);// create the vertex shader

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// tell openGL what the source code of the vertex shader is
	glCompileShader(vertexShader);

	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();
	}
}

void Application::cleanup(){
	std::cout << "cleaning up!\n";

	glfwDestroyWindow(window);// kill the window (murder)
	glfwTerminate();// stop glfw from running

	std::cout << "cleanup finished!\n";
}
