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
	int CUDDLEFISH = 10;
	int CUDDLEFISH_FULL = 20;
	int MUSTARDFISH = 8;
	int COWFISH = 3;
	int BRIMBLE = 3;
	int SHARK = 1;
	int SNOBFISH = 20;
	int GRUMPER = 5;
	int TRUMBLE = 3;
	int PINK_KISSER = 15;
};

const FISHES_NUMBERS FISHES;

constexpr int START_MONEY_AMOUNT = 0;
constexpr int ROD_STRENGTH = 500;
constexpr int ROD_POWER = 500;
constexpr int MAX_LINE_TENSION = 300;

constexpr int COAST_Y = 400;
constexpr int WATER_Y = 590;

constexpr int GRAVITY = 650;
constexpr int CASTING_SPEED = -250;
constexpr int BAIT_FLIGHT_SPEED = 2000;
constexpr int AIR_RESIST = 200;
constexpr int SINK_SPEED = 250;
constexpr int REEL_SPEED = 350;
constexpr int BAIT_ATTRACTION = 40;

const sf::Vector2f FULL_AREA = { 5000, 5000 };
const sf::Vector2f CUDDLEFISH_AREA = { 1000, 1000 };
const sf::Vector2f MUSTARDFISH_AREA = { 5000, 2000 };
const sf::Vector2f COWFISH_AREA = { 3000, 2000 };
const sf::Vector2f BRIMBLE_AREA = { 500, 2000 };
const sf::Vector2f SHARK_AREA = { 5000, 1500 };
const sf::Vector2f SNOBFISH_AREA = { 5000, 1500 };
const sf::Vector2f GRUMPER_AREA = { 5000, 2000 };
const sf::Vector2f TRUMBLE_AREA = { 4000, 2000 };
const sf::Vector2f PINK_KISSER_AREA = { 3000, 3000 };

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