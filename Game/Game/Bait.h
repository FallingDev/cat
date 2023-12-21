#pragma once
#include "Entity.h"
#include "IFish.h"

class Bait final : public Entity
{
public:
	explicit Bait();
	void Throw(float const angle);
	void Update(float const t);
	bool IsThrown() const;
	void Sink(sf::Vector2f const lineStart);
	void Reel(float const t);
	void Eat(IFish* fish);
	void Rebait();
	bool IsInWater();
	IFish* GetFish();

private:
	float m_speedX = 0;
	float m_speedY = 0;
	bool m_isThrown = false;
	bool m_isInWater = false;
	float m_lineLen = 0;
	sf::Vector2f m_lineStart;
	float m_angle = 0;
	IFish* m_caughtFish = nullptr;
};

