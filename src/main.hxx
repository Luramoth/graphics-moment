#pragma once

#include<GLFW/glfw3.h>

/*	"why did you make a header for main.cxx?"
	because i like the order of my functions and i dont want to change them
	
	fuck you*/

void processInput();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);