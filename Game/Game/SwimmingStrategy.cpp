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
		m_angle = GetRandomInt(-45, 45);
	}

	if (m_angle > 0)
	{
		float degrees = 150 * t;
		fish.GetImage().rotate(degrees);
		m_angle -= degrees;
	}

	float radians = ToRadians(fish.GetImage().getRotation());
	fish.GetImage().move(-t * m_speed * std::cos(radians), -t * m_speed * std::sin(radians));
}

void SwimmingStrategy::Start(Entity& fish, float maxSpeed, float boost)
{
	fish.GetImage().setRotation(GetRandomInt(0, 360));
	m_maxSpeed = maxSpeed;
	m_boost = boost;
	m_speed = GetRandomInt(0, m_maxSpeed);
	const int x = GetRandomInt(m_area.left, m_area.left + m_area.width);
	const int y = GetRandomInt(m_area.top, m_area.top + m_area.height);
	fish.GetImage().setPosition(x, y);
}

void SwimmingStrategy::ClampInArea(Entity& fish)
{
	const bool isInArea = m_area.contains(fish.GetImage().getPosition());
	if (!isInArea && m_isInArea)
	{
		m_isInArea = false;
		TurnAround(fish);
	}
	if (isInArea && !m_isInArea)
	{
		m_isInArea = true;
	}
}

void SwimmingStrategy::SetMaxSpeed()
{
	m_speed = m_maxSpeed;
}

void SwimmingStrategy::TurnAround(Entity& fish)
{
	fish.GetImage().rotate(180);
}
