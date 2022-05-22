#include "include/common.hxx"

int main (){
	std::cout << "starting up!\n";

	Application app;

	try
	{
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}