#pragma once
#include "Fish.h"

class MustardFish : public Fish
{
public:
	MustardFish(sf::FloatRect area)
		: Fish(
			"mustardfish.png",
			"mustardfish.png",
			"mustardfish_card.png",
			SwimmingStrategy(area),
			450,
			100,
			80,
			100,
			30,
			15,
			250,
			100,
			Size::Medium,
			{60, 55},
			200
		)
	{}
};