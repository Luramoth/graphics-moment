#include "include/colormod.hxx"
#include "include/glm/fwd.hpp"
#include "include/glm/trigonometric.hpp"
#include "include/opgl.hxx"

#include "main.hxx"

#include <GLFW/glfw3.h>
#include <iostream>

//width and height of the window
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 800;

// a bunch of modifiers for colors
Color::Modifier green(Color::FG_GREEN);
Color::Modifier red(Color::FG_RED);
Color::Modifier yellow(Color::FG_YELLOW);
Color::Modifier def(Color::FG_DEFAULT);

//classes
GLFWwindow *window;

// OpenGL renderer
OpenGL *opgl;

//variables
float cameraSpeed = 2.5f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float currentFrame;

float yaw;
float pitch;

//initialisation function
void init(){
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

	opgl = new OpenGL(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);

	std::cout << green << "project initialised!\n" << def;
}

//main loop function that will run the entire time the program is open
void mainloop(){
	std::cout << yellow << "running main loop\n" << def;

	// while the application isent closed, do everything.
	while (!glfwWindowShouldClose(window)){
		currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// take input from the user
		processInput();

		// render the aggressively magenta window
		glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//render things in OpenGL
		opgl->GLRender();

		// check all call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

//function to get rid of all the stuff that isent needed anymore because the program is closing
void cleanup(){
	std::cout << green << "cleaning up!\n" << def;

	glfwDestroyWindow(window);// destroy the window class
	glfwTerminate();// this closes off GLFW
	delete opgl;// close off OpenGL

	std::cout << green << "cleanup finished!\n" << def;
}

//process all the inputs for the program
void processInput(){
	cameraSpeed = 2.5f * deltaTime;

	//close the window if esc is pressed
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// turn on wireframe if tab is pressed
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS)
		opgl->wireframe = true;
	else
		opgl->wireframe = false;
	
	//WASD          
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		opgl->camera.cameraPos += cameraSpeed * opgl->camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		opgl->camera.cameraPos -= cameraSpeed * opgl->camera.cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		opgl->camera.cameraPos -= glm::normalize(glm::cross(opgl->camera.cameraFront, opgl->camera.cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		opgl->camera.cameraPos += glm::normalize(glm::cross(opgl->camera.cameraFront, opgl->camera.cameraUp)) * cameraSpeed;
}

//resize the viewport when the window gets resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0,0, width, height);
}

// this function gets called when the mouse moves around, at all
void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	float lastX = 400, lastY = 400;

	float xoffset = xpos - lastX;
	float yoffset = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch > -89.0f)
		pitch = -89.0f;
	
	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

//entry point for the program
int main (){
	std::cout << green << "starting up!\n" << def;

	init();
	mainloop();
	cleanup();

	return 0;
}