#include "Bait.h"
#include <corecrt_math_defines.h>

Entity& Bait::Get()
{
    return m_bait;
}

void Bait::Throw(float const angle)
{
    const double radians = M_PI / 180 * angle;
    m_speedX = SPEED * std::cos(radians);
    m_speedY = SPEED * std::sin(radians);
}

void Bait::Update(float const t)
{
    m_bait.GetImage().move(m_speedX * t, m_speedY * t);
}
