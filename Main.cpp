#include <SFML/Graphics.hpp>
#include "Application.h"

#include <stdexcept>
#include <iostream>

int main()
{
	try
	{
		Application game;
		game.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\n\nEXCEPTION: " << e.what() << std::endl;
	}
	


}