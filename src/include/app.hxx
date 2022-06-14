#pragma once

#include "glad/glad.h"
#include "opgl.hxx"

#include <GLFW/glfw3.h>

class Application {
public:
	float cameraSpeed = 2.5f;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	void run();

private:
	//classes
	GLFWwindow *window;

	OpenGL *opgl;

	//variables
	float currentFrame;

	//functions
	void initWindow();
	void mainloop();
	void cleanup();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput();

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};