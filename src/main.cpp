#include <cstdlib>
#include <iostream>

#include "core/GameEngine.h"
#include "core/GameException.h"

#include "pudge-wars/IntroState.h"

int main(int argc, char* argv[])
{
	GameEngine engine;

	try
	{
		engine.initialise();
		engine.pushState(new IntroState());
		engine.run();
	}
	catch(GameException& e)
	{
		std::cerr << e.what() << std::endl;

		return e.exceptionId();
	}

	return EXIT_SUCCESS;
}
