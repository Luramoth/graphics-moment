#include "include/app.hxx"
#include "include/colormod.hxx"

#include<iostream>

int main (){
	Color::Modifier green(Color::FG_GREEN);
	Color::Modifier def(Color::FG_DEFAULT);

	std::cout << green << "starting up!\n" << def;

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