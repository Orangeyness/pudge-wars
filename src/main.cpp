#include <cstdlib>
#include <iostream>

#include "core/GameEngine.h"
#include "core/GameException.h"

#include "pudge-wars/IntroState.h"

void attemptLoadConfigFile(EngineConfig& config, const char* filename)
{
	try 
	{
		config.load(filename);
	}
	catch(GameException& e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << "Failed to load engine config file, using defaults." << std::endl;
	}
}

int main(int argc, char* argv[])
{
	EngineConfig config;
	attemptLoadConfigFile(config, "assets/engine.ini");

	GameEngine engine(&config);
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
