#include "Bait.h"
#include <corecrt_math_defines.h>
#include "Common.h"
#include <algorithm>

Bait::Bait()
    : Entity("large_bait.png")
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

    if (m_isInWater)
    {
        sf::Vector2f delta = GetImage().getPosition() - m_lineStart;
        if (m_caughtFish == nullptr || m_caughtFish->IsTired())
        {
            if (m_angle < M_PI / 2)
            {
                m_angle += t * SINK_SPEED / m_lineLen;
            }
        }
        
        if (m_caughtFish != nullptr)
        {
            m_lineLen += REEL_SPEED * m_resist / ROD_POWER * t;
        }

        if (GetImage().getPosition().y < WATER_Y && ToDegrees(m_angle) < 65)
        {
            m_angle = std::asin((WATER_Y - m_lineStart.y) / m_lineLen);
        }
        
        GetImage().setPosition(m_lineStart + m_lineLen * sf::Vector2f{ std::cos(m_angle), std::sin(m_angle) });
    }
    else
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
    Rebait();
}

void Bait::Reel(float const t)
{
    if (m_isInWater)
    {
        m_lineLen -= REEL_SPEED * t;
        m_totalResist = std::min(m_resist, static_cast<float>(ROD_POWER));

        if (m_lineLen <= GetSize().y / 2)
        {
            m_isThrown = false;
            m_isInWater = false;
            m_angle = M_PI / 2;
            if (m_caughtFish == nullptr)
            {
                Rebait();
            }
            GetImage().setPosition(m_lineStart + m_lineLen * sf::Vector2f{ std::cos(m_angle), std::sin(m_angle) });
        }
    }
}

void Bait::Eat(IFish* fish)
{
    Hide();
    m_caughtFish = fish;
}

void Bait::Rebait()
{
    if (!IsHidden())
    {
        return;
    }

    if (m_caughtFish != nullptr)
    {
        switch (m_caughtFish->GetSize())
        {
        case Size::Small:
            LoadImage("medium_bait.png");
            m_size = Size::Medium;
            break;
        case Size::Medium:
        case Size::Large:
            LoadImage("large_bait.png");
            m_size = Size::Large;
            break;
        default:
            break;
        }

        SetOriginCenter();
        m_caughtFish->HideFish();
    }
    else
    {
        LoadImage("small_bait.png");
        m_size = Size::Small;
    }

    Show();
    m_resist = 0;
    m_caughtFish = nullptr;
}

bool Bait::IsInWater()
{
    return m_isInWater;
}

IFish* Bait::GetFish()
{
    return m_caughtFish;
}

float Bait::GetAngle() const
{
    return m_angle;
}

void Bait::AddAngle(float const angle)
{
    m_angle += angle;
}

void Bait::SetFishResist(float const resist)
{
    m_resist = resist;
}

float Bait::GetResist()
{
    auto resist = m_totalResist;
    m_totalResist = 0;
    return resist;
}

void Bait::BreakLine()
{
    if (m_caughtFish != nullptr)
    {
        m_caughtFish->Uncaught();
        m_caughtFish = nullptr;
        m_resist = 0;
    }
}

int Bait::SellFish()
{
    if (m_caughtFish == nullptr)
    {
        return 0;
    }

    int money = m_caughtFish->Sell();
    m_caughtFish = nullptr;
    return money;
}

Size Bait::GetBaitSize() const
{
    return m_size;
}
