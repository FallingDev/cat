#pragma once
#include "Fish.h"
class Trumble : public Fish
{
public:
	Trumble(sf::FloatRect area)
		: Fish(
			"trumble.png",
			"trumble.png",
			"trumble_card.png",
			SwimmingStrategy(area),
			9400,
			100,
			150,
			500,
			250,
			80,
			200,
			100,
			Size::Large,
			{ 115, 111 },
			400
		)
	{}
};

