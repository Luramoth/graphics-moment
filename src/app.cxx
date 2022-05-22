#include "include/common.hxx"

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class Application {
	public:

	void run(){
		initWindow();
		mainloop();
		cleanup();
	}

	private:
	GLFWwindow* window;// class for the GLFW window

	void initWindow(){
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

	void mainloop(){
		std::cout << "running main loop\n";

		while (!glfwWindowShouldClose(window)){
			glfwPollEvents();
		}
	}

	void cleanup(){
		std::cout << "cleaning up!\n";

		glfwDestroyWindow(window);// kill the window (murder)
		glfwTerminate();// stop glfw from running

		std::cout << "cleanup finished!\n";
	}
};