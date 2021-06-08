#pragma once
#include <SDL2/SDL.h>

template<typename T>
struct Vec2
{
	T x;
	T y;

	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}
	Vec2 operator*(const float& rhs) const
	{
		return { x * rhs, y * rhs };
	}
};

SDL_Window* window{nullptr};
SDL_Renderer* renderer{nullptr};

bool is_running{true};

Uint32 ticks_count{0};

Vec2<float> ball_pos{200.f, 200.f};
Vec2<float> ball_vel{-200.f, 235.f};
Vec2<float> paddle_pos{30.f, 300.f};

const int thickness{20};

int8_t paddle_dir{0};
const int paddle_h{100};

float paddle_speed{300.f};
