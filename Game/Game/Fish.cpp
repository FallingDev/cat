#include "Fish.h"
#include "Common.h"

Fish::Fish(std::string&& filename, SwimmingStrategy swimmingStrategy)
	: Entity(std::move(filename))
	, m_swimmingStrategy(swimmingStrategy)
	
{
	SetOriginCenter();
	m_swimmingStrategy.Start(*this, 100, 5);
}

void Fish::Update(float const t, Bait& bait)
{
	m_swimmingStrategy.Swim(*this, t, bait);
}
