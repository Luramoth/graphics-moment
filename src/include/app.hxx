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
	GLFWwindow *window;

	OpenGL *opgl;

	float currentFrame;

	void initWindow();
	void mainloop();
	void cleanup();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput();
};