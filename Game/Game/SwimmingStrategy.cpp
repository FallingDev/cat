#include "SwimmingStrategy.h"
#include "Common.h"

SwimmingStrategy::SwimmingStrategy(sf::FloatRect area)
	: m_area(area)
{
}

void SwimmingStrategy::Swim(Entity& fish, float const t, Bait& bait)
{
	ClampInArea(fish);

	m_speed += m_boost * t * (m_isSlowDown ? -1 : 1);
	if (m_speed > m_maxSpeed)
	{
		m_isSlowDown = true;
	}

	if (m_speed < 0)
	{
		m_isSlowDown = false;
		m_angle += GetRandomInt(-45, 45);
	}

	float radians = ToRadians(m_angle);
	fish.GetImage().setRotation(m_angle);
	fish.GetImage().move(-t * m_speed * std::cos(radians), -t * m_speed * std::sin(radians));
}

void SwimmingStrategy::Start(Entity& fish, float maxSpeed, float boost)
{
	m_angle = GetRandomInt(0, 360);
	m_maxSpeed = maxSpeed;
	m_boost = boost;
	m_speed = GetRandomInt(0, m_maxSpeed);
	const int x = GetRandomInt(m_area.left, m_area.left + m_area.width);
	const int y = GetRandomInt(m_area.top, m_area.top + m_area.height);
	fish.GetImage().setPosition(x, y);
	fish.GetImage().setRotation(m_angle);
}

void SwimmingStrategy::ClampInArea(Entity& fish)
{
	const bool isInArea = m_area.contains(fish.GetImage().getPosition());
	if (!isInArea && m_isInArea)
	{
		m_isInArea = false;
		TurnAround();
	}
	if (isInArea && !m_isInArea)
	{
		m_isInArea = true;
	}
}

void SwimmingStrategy::TurnAround()
{
	m_angle += 180;
}
