#include "Fish.h"
#include "Common.h"

Fish::Fish(std::string&& filename, SwimmingStrategy swimmingStrategy)
	: Entity(std::move(filename))
	, m_swimmingStrategy(swimmingStrategy)
	
{
	SetOriginCenter();
	m_swimmingStrategy.Start(*this, 100, 70);
}

void Fish::Update(float const t, Bait& bait)
{
	if (m_caught)
	{
		if (!m_sold)
		{
			GetImage().setPosition(bait.GetImage().getPosition());
		}
		else if (GetImage().getPosition().x > m_soldX)
		{
			GetImage().move(-100 * t, 0);
		}
		return;
	}

	HuntBait(t, bait);
	m_swimmingStrategy.Swim(*this, t, bait);
}

int Fish::Sell()
{
	GetImage().setPosition(GetImage().getPosition().x, COAST_Y + GetRandomInt(40, 90));
	m_sold = true;
	m_soldX = GetRandomInt(50, 250);
	return m_price;
}

void Fish::HuntBait(float const t, Bait& bait)
{
	sf::Vector2f delta = GetImage().getPosition() - bait.GetImage().getPosition();
	const float distanceToBait = std::hypot(delta.x, delta.y);
	const float angleToBait = ToRadians(std::atan2(delta.y, delta.x));

	if (distanceToBait > BAIT_ATTRACTION || (!m_caught && bait.IsHidden()))
	{
		return;
	}

	GetImage().setRotation(angleToBait);
	GetImage().setPosition(bait.GetImage().getPosition());
	m_caught = true;
	bait.Eat(this);
}
