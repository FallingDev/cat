#include "SwimmingStrategy.h"
#include "Common.h"

SwimmingStrategy::SwimmingStrategy(sf::FloatRect area)
	: m_area(area)
{
}

void SwimmingStrategy::Swim(Entity& fish, float const t)
{
	fish.GetImage().move(t * m_speed * std::cos(m_angle), t * m_speed * std::cos(m_angle));
}

void SwimmingStrategy::Start(Entity& fish, float maxSpeed)
{
	m_angle = GetRandomInt(0, 360);
	m_maxSpeed = maxSpeed;
	fish.GetImage().setPosition(GetRandomInt(m_area.left, m_area.left + m_area.width), GetRandomInt(m_area.top, m_area.top + m_area.height));
	fish.GetImage().setRotation(m_angle);
}

void SwimmingStrategy::ClampInArea(Entity& fish)
{
}

void SwimmingStrategy::SetArea(sf::FloatRect&& area)
{
	m_area = std::move(area);
}
