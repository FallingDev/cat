#pragma once
#include "Fish.h"
class CowFish : public Fish
{
public:
	CowFish(sf::FloatRect area)
		: Fish(
			"cowfish.png",
			"cowfish.png",
			"cowfish_card.png",
			SwimmingStrategy(area),
			2500,
			70,
			70,
			200,
			100,
			10,
			300,
			70,
			Size::Large,
			{ 90, 117 },
			150
		)
	{}
};

