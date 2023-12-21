#pragma once
#include "Entity.h"
#include "SwimmingStrategy.h"
#include "IFish.h"
#include "Bait.h"

class Fish : public Entity, public IFish
{
public:
	Fish(std::string&& filename, SwimmingStrategy swimmingStrategy = SwimmingStrategy());
	void Update(float const t, Bait& bait);
	int Sell() override;

private:
	void HuntBait(float const t, Bait& bait);

private:
	SwimmingStrategy m_swimmingStrategy;
	bool m_caught = false;
	int m_price = 50;
	int m_soldX = 0;
	bool m_sold = false;
};

