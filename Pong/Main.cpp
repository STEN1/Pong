#include "Game.h"


void process_input()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				is_running = false;
				break;
			default:
				break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);

	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		is_running = false;
	}

	paddle_dir = 0;
	
	if (keyboardState[SDL_SCANCODE_W])
	{
		paddle_dir -= 1;
	}

	if (keyboardState[SDL_SCANCODE_S])
	{
		paddle_dir += 1;
	}
}

float update_delta_time()
{
	// limit framerate to 16ms (60fps)
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count + 16))
	{
	}
	
	// convert from ms to s
	float deltaTime = (SDL_GetTicks() - ticks_count) / 1000.f;
	// tick count for next frame
	ticks_count = SDL_GetTicks();

	// clamp deltaTime. dont want delaTime to be to large after debugging.
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	return deltaTime;
}

void update_game()
{
	const float deltaTime = update_delta_time();

	paddle_pos.y += static_cast<float>(paddle_dir) * paddle_speed * deltaTime;

	if (paddle_pos.y < paddle_h/2.f + thickness)
	{
		paddle_pos.y = paddle_h/2.f + thickness;
	}
	else if (paddle_pos.y > 768 - (paddle_h/2.f + thickness))
	{
		paddle_pos.y = 768 - (paddle_h/2.f + thickness);
	}

	ball_pos += ball_vel * deltaTime;
}

void generate_output()
{
	// clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);

	// draw walls
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	

	SDL_Rect rightWall{	1024 - thickness,	 0,
		thickness, 768 	};
	SDL_RenderFillRect(renderer, &rightWall);

	SDL_Rect roof{ 0, 0, 1024, thickness	};
	SDL_RenderFillRect(renderer, &roof);

	SDL_Rect floor{ 0, 768 - thickness,
		1024, thickness	};
	SDL_RenderFillRect(renderer, &floor);

	SDL_Rect ball{ static_cast<int>(ball_pos.x - thickness / 2.f), static_cast<int>(ball_pos.y - thickness / 2.f),
		thickness, thickness	};
	SDL_RenderFillRect(renderer, &ball);
	
	SDL_Rect paddle{ static_cast<int>(paddle_pos.x - thickness / 2.f), static_cast<int>(paddle_pos.y - paddle_h / 2.f),
		thickness, paddle_h };
	SDL_RenderFillRect(renderer, &paddle);
	
	SDL_RenderPresent(renderer);
}

bool initialize()
{
	const int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		return false;
	}

	window = SDL_CreateWindow("Pong", 100, 100, 1024, 768, 0);

	if (!window)
	{
		SDL_Log("Unable to create window SDL: %s", SDL_GetError());

		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (!renderer)
	{
		SDL_Log("Unable to create renderer SDL: %s", SDL_GetError());

		return false;
	}
	
	return true;
}

void run_loop()
{
	while (is_running)
	{
		process_input();

		update_game();

		generate_output();
	}
}

void shutdown()
{
	SDL_DestroyRenderer(renderer);
	
	SDL_DestroyWindow(window);
	
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