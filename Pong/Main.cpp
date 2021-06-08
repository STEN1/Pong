#include "Game.h"


void process_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
			default:
				break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void update_game()
{
}

void generate_output()
{
	// clear screen
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	// draw walls
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	const int thickness{20};

	SDL_Rect rightWall{	1024 - thickness,	 0,
		thickness, 768 	};
	SDL_RenderFillRect(mRenderer, &rightWall);

	SDL_Rect roof{ 0, 0, 1024, thickness	};
	SDL_RenderFillRect(mRenderer, &roof);

	SDL_Rect floor{ 0, 768 - thickness,
		1024, thickness	};
	SDL_RenderFillRect(mRenderer, &floor);

	SDL_Rect ball{ static_cast<int>(ballPos.x - thickness / 2.f), static_cast<int>(ballPos.y - thickness / 2.f),
		thickness, thickness	};
	SDL_RenderFillRect(mRenderer, &ball);
	
	SDL_Rect paddle{ static_cast<int>(paddlePos.x - thickness / 2.f), static_cast<int>(paddlePos.y - thickness / 2.f),
		thickness, static_cast<int>(thickness * 5.f) };
	SDL_RenderFillRect(mRenderer, &paddle);
	
	SDL_RenderPresent(mRenderer);
}

bool initialize()
{
	const int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return false;
	}

	mWindow = SDL_CreateWindow("Pong", 100, 100, 1024, 768, 0);

	if (!mWindow)
	{
		SDL_Log("Unable to create window SDL: %s", SDL_GetError());

		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!mRenderer)
	{
		SDL_Log("Unable to create renderer SDL: %s", SDL_GetError());

		return false;
	}
	
	return true;
}

void run_loop()
{
	while (mIsRunning)
	{
		process_input();

		update_game();

		generate_output();
	}
}

void shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	
	SDL_DestroyWindow(mWindow);
	
	SDL_Quit();
}


int main(int argc, char** argv)
{

	const bool initialized = initialize();

	if (initialized)
	{
		run_loop();
	}

	shutdown();
	
	return 0;
}