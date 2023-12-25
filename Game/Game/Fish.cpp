#include "Fish.h"
#include "Common.h"

Fish::Fish
(
	std::string&& filename,
	SwimmingStrategy swimmingStrategy,
	int price,
	int power,
	float rotationSpeed,
	int maxStamina,
	int weight,
	int recoverySpeed,
	int maxSpeed,
	int boost
)
	: Entity(std::move(filename))
	, m_swimmingStrategy(swimmingStrategy)
	, m_price(price)
	, m_power(power)
	, m_rotationSpeed(rotationSpeed)
	, m_maxStamina(maxStamina)
	, m_weight(weight)
	, m_recoverySpeed(recoverySpeed)
{
	SetOriginCenter();
	m_swimmingStrategy.Start(*this, maxSpeed, boost);
	m_stamina = m_maxStamina;
}

void Fish::Update(float const t, Bait& bait)
{
	FlipFish();

	if (m_caught)
	{
		if (!m_sold)
		{
			Fight(t, bait);
		}
		else if (GetImage().getPosition().x > m_soldX)
		{
			GetImage().move(-100 * t, 0);
		}
		return;
	}

	HuntBait(t, bait);
	m_swimmingStrategy.Swim(*this, t, bait);
}

int Fish::Sell()
{
	GetImage().setPosition(GetImage().getPosition().x, COAST_Y + GetRandomInt(40, 90));
	m_sold = true;
	m_soldX = GetRandomInt(50, 250);
	return m_price;
}

void Fish::Uncaught()
{
	m_caught = false;
}

bool Fish::IsTired() const
{
	return m_tired;
}

void Fish::HuntBait(float const t, Bait& bait)
{
	sf::Vector2f delta = GetImage().getPosition() - bait.GetImage().getPosition();
	const float distanceToBait = std::hypot(delta.x, delta.y);
	const float angleToBait = ToRadians(std::atan2(delta.y, delta.x));

	if (distanceToBait > BAIT_ATTRACTION || (!m_caught && bait.IsHidden()))
	{
		return;
	}

	GetImage().setRotation(angleToBait);
	GetImage().setPosition(bait.GetImage().getPosition());
	m_caught = true;
	bait.Eat(this);
}

void Fish::Fight(float const t, Bait& bait)
{
	GetImage().setPosition(bait.GetImage().getPosition());
	float baitAngle = ToDegrees(bait.GetAngle());
	float fishRotation = GetImage().getRotation();
	float delta = fishRotation - baitAngle;

	if (m_tired)
	{
		GetImage().rotate(delta > 5 ? -m_rotationSpeed * t : m_rotationSpeed * t);
		m_stamina += m_recoverySpeed * t;
		if (m_stamina > m_maxStamina)
		{
			m_tired = false;
		}

		return;
	}

	float degrees = 0;
	if (delta > 180)
	{
		degrees = m_power * std::cos(ToRadians(270 - delta)) * t;
	}
	else
	{
		degrees = -m_power * std::cos(ToRadians(90 - delta)) * t;
	}
	bait.AddAngle(ToRadians(degrees * 0.1));

	if (delta > 90 && delta < 270)
	{
		float power = m_power * std::sin(ToRadians(delta - 90));
		bait.SetFishResist(m_weight + power);
		m_stamina -= power * t;
		if (m_stamina < 0)
		{
			m_tired = true;
			bait.SetFishResist(m_weight);
		}
	}

	if (m_isRightRotate)
	{
		if (delta < 150)
		{
			m_isRightRotate = false;
		}
	}
	else
	{
		if (delta > 210)
		{
			m_isRightRotate = true;
		}
	}
	
	GetImage().rotate(m_isRightRotate ? -m_rotationSpeed * t : m_rotationSpeed * t);
}

void Fish::FlipFish()
{
	float rotation = GetImage().getRotation();
	if (rotation > 90 && rotation < 270 && IsFlipped() )
	{
		Flip();
	}

	if (!(rotation > 90 && rotation < 270) && !IsFlipped())
	{
		Flip();
	}
}
