#include "Bait.h"
#include <corecrt_math_defines.h>
#include "Common.h"

Bait::Bait()
    : Entity("bait.png")
{
}

void Bait::Throw(float const angle)
{
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

    if (m_isInWater && m_angle < M_PI / 2)
    {
        sf::Vector2f delta = GetImage().getPosition() - m_lineStart;
        m_angle += t * SINK_SPEED / m_lineLen;

        GetImage().setPosition(m_lineStart + m_lineLen * sf::Vector2f{ std::cos(m_angle), std::sin(m_angle) });
    }

    if (!m_isInWater)
    {
        GetImage().move(m_speedX * t, m_speedY * t);
        m_speedY += GRAVITY * t;
        if (m_speedX > 0)
        {
            m_speedX -= AIR_RESIST * t;
        }
    }
}

bool Bait::IsThrown() const
{
    return m_isThrown;
}

void Bait::Sink(sf::Vector2f const lineStart)
{
    if (m_isInWater)
    {
        return;
    }

    m_isInWater = true;
    m_lineStart = lineStart;
    sf::Vector2f delta = GetImage().getPosition() - m_lineStart;
    m_lineLen = std::hypot(delta.x, delta.y);
    m_angle = std::atan2(delta.y, delta.x);
}
