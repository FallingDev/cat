#include "Fish.h"

Fish::Fish(std::string&& filename, SwimmingStrategy swimmingStrategy)
	: Entity(std::move(filename))
	, m_swimmingStrategy(swimmingStrategy)
	
{
	m_swimmingStrategy.Start(*this, 10);
}

void Fish::Update(float const t)
{
	m_swimmingStrategy.Swim(*this, t);
}

void Fish::SetArea(sf::FloatRect area)
{
	m_swimmingStrategy.SetArea(std::move(area));
	m_swimmingStrategy.Start(*this, 10);
}
