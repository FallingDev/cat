#pragma once
#include "Entity.h"
#include "SwimmingStrategy.h"

class Fish : public Entity
{
public:
	Fish(std::string&& filename, SwimmingStrategy swimmingStrategy = SwimmingStrategy());
	void Update(float const t);
	void SetArea(sf::FloatRect area);

private:
	SwimmingStrategy m_swimmingStrategy;
};

