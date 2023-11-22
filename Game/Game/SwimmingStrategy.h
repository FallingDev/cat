#pragma once
#include "Entity.h"

class SwimmingStrategy
{
public:
	SwimmingStrategy(sf::FloatRect area = sf::FloatRect(0, 0, 300, 300));
	virtual void Swim(Entity& fish, float const t);
	void Start(Entity& fish, float maxSpeed);
	void ClampInArea(Entity& fish);
	void SetArea(sf::FloatRect&& area);

private:
	sf::FloatRect m_area;
	float m_maxSpeed = 0;
	float m_speed = 0;
	float m_angle = 0;
};

