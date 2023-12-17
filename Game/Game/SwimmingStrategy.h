#pragma once
#include "Entity.h"
#include "Bait.h"

class SwimmingStrategy
{
public:
	SwimmingStrategy(sf::FloatRect area = sf::FloatRect(0, 0, 300, 300));
	virtual void Swim(Entity& fish, float const t, Bait& bait);
	void Start(Entity& fish, float maxSpeed, float boost);
	void ClampInArea(Entity& fish);

private:
	void TurnAround();

private:
	sf::FloatRect m_area;
	float m_maxSpeed = 0;
	float m_boost = 0;
	float m_speed = 0;
	float m_angle = 0;
	bool m_isInArea = true;
	bool m_isSlowDown = false;
	bool m_caught = false;
};

