#include "include/common.hxx"

class Application {
	public:

	void run(){
		initWindow();
		mainloop();
		cleanup();
	}

	private:

	void initWindow(){
		glfwInit();

		std::cout << "project initialised!\n";
	}

	void mainloop(){
		std::cout << "running main loop\n";
	}

	void cleanup(){
		std::cout << "cleaning up!\n";

		glfwTerminate();// stop glfw from running

		std::cout << "cleanup finished!\n";
	}
};