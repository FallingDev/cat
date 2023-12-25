#pragma once
#include "Fish.h"
class CuddleFish : public Fish
{
public:
	CuddleFish(sf::FloatRect area)
		: Fish(
			"cuddlefish.png",
			SwimmingStrategy(area),
			50,
			30,
			80,
			50,
			5,
			5,
			100,
			70
		)
	{}
};

