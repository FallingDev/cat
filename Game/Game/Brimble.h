#pragma once
#include "Fish.h"
class Brimble : public Fish
{
public:
	Brimble(sf::FloatRect area)
		: Fish(
			"brimble.png",
			"brimble.png",
			"brimble_card.png",
			SwimmingStrategy(area),
			8500,
			100,
			70,
			500,
			250,
			100,
			100,
			70,
			Size::Large,
			{ 88, 93 },
			600
		)
	{}
};

