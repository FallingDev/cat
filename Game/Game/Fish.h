#pragma once
#include "Entity.h"
#include "SwimmingStrategy.h"
#include "Bait.h"

class Fish : public Entity
{
public:
	Fish(std::string&& filename, SwimmingStrategy swimmingStrategy = SwimmingStrategy());
	void Update(float const t, Bait& bait);

private:
	SwimmingStrategy m_swimmingStrategy;
};

