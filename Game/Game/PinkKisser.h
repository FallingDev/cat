#pragma once
#include "Fish.h"
class PinkKisser : public Fish
{
public:
	PinkKisser(sf::FloatRect area)
		: Fish(
			"pink_kisser.png",
			"pink_kisser_eaten.png",
			"pink_kisser_card.png",
			SwimmingStrategy(area),
			9800,
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

