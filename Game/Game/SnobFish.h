#pragma once
#include "Fish.h"
class SnobFish : public Fish
{
public:
	SnobFish(sf::FloatRect area)
		: Fish(
			"snobfish.png",
			"snobfish_eaten.png",
			"snobfish_card.png",
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
			{ 10, 45 },
			200
		)
	{}
};

