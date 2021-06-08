#pragma once
#include <SDL2/SDL.h>

template<typename T>
struct Vec2
{
	T x;
	T y;
};

SDL_Window* mWindow{nullptr};
SDL_Renderer* mRenderer{nullptr};

bool mIsRunning{true};

Vec2<float> ballPos{200.f, 200.f};
Vec2<float> paddlePos{30.f, 300.f};
