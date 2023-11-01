#include "Bait.h"
#include <corecrt_math_defines.h>
#include "Common.h"

Bait::Bait()
    : Entity("bait.png")
{
}

void Bait::Throw(float const angle)
{
    auto delta = GetImage().getOrigin();
    GetImage().setOrigin(0, 0);
    GetImage().move(-delta);

    m_isThrown = true;
    const double radians = M_PI / 180 * angle;
    m_speedX = BAIT_FLIGHT_SPEED * std::cos(radians);
    m_speedY = BAIT_FLIGHT_SPEED * std::sin(radians);
}

void Bait::Update(float const t)
{
    if (!m_isThrown)
    {
        return;
    }
    GetImage().move(m_speedX * t, m_speedY * t);
    m_speedY += GRAVITY * t;
    if (m_speedX > 0)
    {
        m_speedX -= AIR_RESIST * t;
    }
}

bool Bait::IsThrown() const
{
    return m_isThrown;
}
