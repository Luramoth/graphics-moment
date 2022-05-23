#include "include/app.hxx"
#include <iostream>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;


void Application::run(){
	initWindow();
	mainloop();
	cleanup();
}

void Application::initWindow() {
	

	std::cout << "project initialised!\n";
}

void Application::mainloop(){
	std::cout << "running main loop\n";
}

void Application::cleanup(){
	std::cout << "cleaning up!\n";

	std::cout << "cleanup finished!\n";
}
