#pragma once
#include "Fish.h"
class CuddleFish : public Fish
{
public:
	CuddleFish(sf::FloatRect area)
		: Fish(
			"cuddlefish.png",
			"cuddlefish_eaten.png",
			"cuddlefish_card.png",
			SwimmingStrategy(area),
			50,
			30,
			80,
			50,
			5,
			5,
			100,
			70,
			Size::Small,
			{10, 47},
			200
		)
	{}
};

