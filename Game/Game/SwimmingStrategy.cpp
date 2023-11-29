#include "SwimmingStrategy.h"
#include "Common.h"

SwimmingStrategy::SwimmingStrategy(sf::FloatRect area)
	: m_area(area)
{
}

void SwimmingStrategy::Swim(Entity& fish, float const t, Bait& bait)
{
	HuntBait(fish, t, bait);

	if (m_speed < m_maxSpeed)
	{
		m_speed += m_boost * t;
	}

	float radians = ToRadians(m_angle);
	fish.GetImage().move(-t * m_speed * std::cos(radians), -t * m_speed * std::sin(radians));
}

void SwimmingStrategy::Start(Entity& fish, float maxSpeed, float boost)
{
	m_angle = GetRandomInt(0, 360);
	m_maxSpeed = maxSpeed;
	m_boost = boost;
	fish.GetImage().setPosition(GetRandomInt(m_area.left, m_area.left + m_area.width), GetRandomInt(m_area.top, m_area.top + m_area.height));
	fish.GetImage().setRotation(m_angle);
}

void SwimmingStrategy::ClampInArea(Entity& fish)
{
}

void SwimmingStrategy::HuntBait(Entity& fish, float const t, Bait& bait)
{
	sf::Vector2f delta = fish.GetImage().getPosition() - bait.GetImage().getPosition();
	const float distanceToBait = std::hypot(delta.x, delta.y);
	const float angleToBait = std::atan2(delta.y, delta.x);

	if (distanceToBait > BAIT_ATTRACTION)
	{
		return;
	}

	fish.GetImage().setRotation(angleToBait);
	fish.GetImage().setPosition(bait.GetImage().getPosition());
}
