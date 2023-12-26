#pragma once
#include "Entity.h"
#include "SwimmingStrategy.h"
#include "IFish.h"
#include "Bait.h"

class Fish : public Entity, public IFish
{
public:
	Fish
	(
		std::string&& filename,
		std::string&& filenameEaten,
		SwimmingStrategy swimmingStrategy,
		int price,
		int power,
		float rotationSpeed,
		int maxStamina,
		int weight,
		int recoverySpeed,
		int maxSpeed,
		int boost,
		Size size,
		sf::Vector2f origin,
		int sence
	);
	void Update(float const t, Bait& bait);
	int Sell() override;
	void Uncaught() override;
	bool IsTired() const override;
	Size GetSize() const override;
	void HideFish() override;
	void Eat() override;
	bool IsEaten() const override;

private:
	void HuntBait(float const t, Bait& bait);
	void Fight(float const t, Bait& bait);
	void FlipFish();

private:
	SwimmingStrategy m_swimmingStrategy;
	bool m_caught = false;
	int m_price;
	int m_soldX = 0;
	bool m_sold = false;
	int m_power;
	float m_rotationSpeed;
	bool m_isRightRotate = false;
	bool m_tired = false;
	int m_maxStamina;
	float m_stamina = m_maxStamina;
	int m_weight;
	int m_recoverySpeed;
	Size m_size;
	float m_sence;
	std::string m_filenameEaten;
	bool m_eaten = false;
};

