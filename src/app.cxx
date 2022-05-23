#include "include/app.hxx"
#include <GLFW/glfw3.h>
#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

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
	std::cout << "initialising project\n";

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
	window = glfwCreateWindow(WIDTH, HEIGHT, "graphic moment, really crazy stuff, though i winder if theres a limit to how long i can make this wondow title", NULL, NULL);

	if (window == NULL) { // if the window couldent be made then its ok to error out
		glfwTerminate();
		std::cerr << "failed to initialise window\n";
	}

	std::cout << "project initialised!\n";
}

// this is the function that contains the loop that cycles through everything the program runs on
void Application::mainloop(){
	std::cout << "running main loop\n";
}

// this function runs when the program is closing and it clears everything up for memory safety
void Application::cleanup(){
	std::cout << "cleaning up!\n";

	glfwTerminate();// this closes off GLFW

	std::cout << "cleanup finished!\n";
}
