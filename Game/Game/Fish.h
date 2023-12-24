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
	void Uncaught() override;
	bool IsTired() const override;

private:
	void HuntBait(float const t, Bait& bait);
	void Fight(float const t, Bait& bait);
	void FlipFish();

private:
	SwimmingStrategy m_swimmingStrategy;
	bool m_caught = false;
	int m_price = 50;
	int m_soldX = 0;
	bool m_sold = false;
	int m_power = 30;
	float m_rotationSpeed = 80;
	bool m_isRightRotate = false;
	bool m_tired = false;
	int m_maxStamina = 70;
	float m_stamina = m_maxStamina;
	int m_weight = 5;
	int m_recoverySpeed = 2;
};

