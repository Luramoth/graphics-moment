#pragma once

#include "glad/glad.h"

#include <GLFW/glfw3.h>

class Application {
public:
	void run();

private:
	GLFWwindow *window;

	void initWindow();
	void mainloop();
	void cleanup();

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processInput();
};