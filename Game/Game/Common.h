#pragma once
#include <corecrt_math_defines.h>

constexpr int GRAVITY = 1000;
constexpr int CASTING_SPEED = -200;
constexpr int BAIT_FLIGHT_SPEED = 1000;
constexpr int AIR_RESIST = 100;

inline float ToRadians(double const degrees)
{
	return M_PI * 2 / 360 * degrees;
}