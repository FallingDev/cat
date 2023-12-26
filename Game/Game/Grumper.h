#pragma once
#include "Fish.h"

class Grumper : public Fish
{
public:
	Grumper(sf::FloatRect area)
		: Fish(
			"grumper.png",
			"grumper.png",
			"grumper_card.png",
			SwimmingStrategy(area),
			800,
			100,
			80,
			150,
			50,
			75,
			400,
			100,
			Size::Medium,
			{ 69, 55 },
			200
		)
	{}
};