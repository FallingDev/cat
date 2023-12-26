#pragma once
#include <corecrt_math_defines.h>
#include <random>

enum class Size
{
	Small,
	Medium,
	Large
};

struct FISHES_NUMBERS
{
	int CUDDLEFISH = 15;
	int MUSTARDFISH = 5;
};

const FISHES_NUMBERS FISHES;

constexpr int START_MONEY_AMOUNT = 500;
constexpr int ROD_STRENGTH = 500;
constexpr int ROD_POWER = 500;
constexpr int MAX_LINE_TENSION = 100;

constexpr int COAST_Y = 400;
constexpr int WATER_Y = 590;

constexpr int GRAVITY = 800;
constexpr int CASTING_SPEED = -250;
constexpr int BAIT_FLIGHT_SPEED = 1800;
constexpr int AIR_RESIST = 300;
constexpr int SINK_SPEED = 200;
constexpr int REEL_SPEED = 250;
constexpr int BAIT_ATTRACTION = 40;
const sf::Vector2f CUDDLEFISH_AREA = { 2000, 1000 };
const sf::Vector2f MUSTARDFISH_AREA = { 3000, 1000 };

inline float ToRadians(double const degrees)
{
	return M_PI * 2 / 360 * degrees;
}

inline float ToDegrees(float const radians)
{
	return 360 * radians / (2 * M_PI);
}

inline int GetRandomInt(int min, int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, max - min);

	return dist(rng) + min;
}

inline bool Equal(float const a, float const b)
{
	return std::abs(a - b) <= 1e-7;
}