#include "include/app.hxx"
#include "include/colormod.hxx"

#include <GLFW/glfw3.h>
#include <cstddef>
#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);

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

//public

// function that goes through a lost of steps to successfully run through the program
void Application::run(){
	initWindow();
	mainloop();
	cleanup();
}

//private

// this initialises the program and gets everything running that needs to start running
void Application::initWindow() {
	std::cout << yellow << "initialising project\n" << def;

	glfwInit();// this starts up GLFW

	// tell GLFW which version of OpenGl to run, in this case its 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// tell GLFW to use the OpenGl core profile and NOT compatability mode as we dont need any kind of legacy code
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); //thing specifically for macos
	#endif

	//create window
	window = glfwCreateWindow(WIDTH, HEIGHT, "graphic moment, really crazy stuff, though i winder if theres a limit to how long i can make this window title as there is nothing telling me i have any kind of limit to how long this thing can be, so ill just keep typing this out until something happens, though so far nothing has happened i suppose so i will just continue on typing until this probably creates a overflow error though its noy my fault the GLFW devs dident think that someone might just make their title this long honestly, this reminds me of this one time, what? did you think i was gonna tell you what  this one time was? thats an invasion of my privacy, all i said was that i was reminded of something", NULL, NULL);

	if (window == NULL) { // if the window couldn't be made then its ok to error out
		glfwTerminate();
		std::cerr << red << "failed to initialise window\n" << def;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << red << "failed to initialise GLAD\n" << def;// if GLAD cant start then throw an error
	}

	glViewport(0, 0, WIDTH, HEIGHT);// set the viewport size  to the size of the window

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// tell GLFW to call this function when the viewport gets resized

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

	std::cout << green << "project initialised!\n" << def;
}

// this is the function that contains the loop that cycles through everything the program runs on
void Application::mainloop(){
	std::cout << yellow << "running main loop\n" << def;

	// while the application isent closed, do everything.
	while (!glfwWindowShouldClose(window)){
		// take input from the user
		processInput();

		// render the aggressively magenta window
		glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// check all call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

// this function runs when the program is closing and it clears everything up for memory safety
void Application::cleanup(){
	std::cout << green << "cleaning up!\n" << def;

	glfwDestroyWindow(window);// destroy the window class
	glfwTerminate();// this closes off GLFW

	std::cout << green << "cleanup finished!\n" << def;
}

// this function changes the size of the OpenGL viewport when the window resizes
void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
}

// get some input data from GLFW to close the window when esc is pressed
void Application::processInput(){
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}