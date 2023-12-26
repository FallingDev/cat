#pragma once
#include "Fish.h"
class Shark : public Fish
{
public:
	Shark(sf::FloatRect area)
		: Fish(
			"shark.png",
			"shark.png",
			"shark_card.png",
			SwimmingStrategy(area),
			64000,
			200,
			200,
			800,
			200,
			200,
			500,
			150,
			Size::Large,
			{ 216, 158 },
			600
		)
	{}
};