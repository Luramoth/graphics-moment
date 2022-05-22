#include "include/common.hxx"

int main (){
	std::cout << "starting up!\n";

	Application app;

	try
	{
		app.run();// try to run the application without error
	}
	catch(const std::exception& e)// if there is an error then stop and say what it is and close the program
	{
		std::cerr << e.what() << '\n';
		return 1;
	}

	return 0;
}