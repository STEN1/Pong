#include "Game.h"

Game::Game()
	:mIsRunning(true)
	,mWindow(nullptr)
	,mRenderer(nullptr)
{
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

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

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();

		UpdateGame();

		GenerateOutput();
	}
}

void Game::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	
	SDL_DestroyWindow(mWindow);
	
	SDL_Quit();
}

void Game::ProcessInput()
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

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
	// clear screen
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
	SDL_RenderClear(mRenderer);

	// draw paddle
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect paddle{}
	SDL_RenderFillRect(mRenderer, &paddle);
	
	SDL_RenderPresent(mRenderer);
}
