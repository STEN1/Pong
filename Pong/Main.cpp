#include "Game.h"


int main(int argc, char** argv)
{
	Game game;

	const bool initialized = game.Initialize();

	if (initialized)
	{
		game.RunLoop();
	}

	game.Shutdown();
	
	return 0;
}