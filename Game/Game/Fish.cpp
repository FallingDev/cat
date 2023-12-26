#include "Fish.h"
#include "Common.h"

Fish::Fish
(
	std::string&& filename,
	std::string&& filenameEaten,
	std::string&& filenameCard,
	SwimmingStrategy swimmingStrategy,
	int price,
	int power,
	float rotationSpeed,
	int maxStamina,
	int weight,
	int recoverySpeed,
	int maxSpeed,
	int boost,
	Size size,
	sf::Vector2f origin,
	int sence
)
	: Entity(std::move(filename))
	, m_filenameEaten(std::move(filenameEaten))
	, m_swimmingStrategy(swimmingStrategy)
	, m_price(price)
	, m_power(power)
	, m_rotationSpeed(rotationSpeed)
	, m_maxStamina(maxStamina)
	, m_weight(weight)
	, m_recoverySpeed(recoverySpeed)
	, m_size(size)
	, m_sence(sence)
{
	GetImage().setOrigin(origin);
	m_swimmingStrategy.Start(*this, maxSpeed, boost);
	m_stamina = m_maxStamina;
	m_card = std::make_shared<Entity>(std::move(filenameCard));
	m_card->GetImage().setPosition(460, 100);
}

void Fish::Update(float const t, Bait& bait)
{
	if (IsHidden())
	{
		return;
	}

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

	m_swimmingStrategy.Swim(*this, t, bait);
	HuntBait(t, bait);
}

int Fish::Sell()
{
	GetImage().setPosition(GetImage().getPosition().x, COAST_Y + GetRandomInt(40, 90));
	m_sold = true;
	m_soldX = GetRandomInt(50, 250);
	return m_price - (m_eaten ? m_price / 2 : 0);
}

void Fish::Uncaught()
{
	m_caught = false;
}

bool Fish::IsTired() const
{
	return m_tired;
}

Size Fish::GetSize() const
{
	return m_size;
}

void Fish::HideFish()
{
	Hide();
}

void Fish::Eat()
{
	m_eaten = true;
	LoadImage(m_filenameEaten);
}

bool Fish::IsEaten() const
{
	return m_eaten;
}

std::shared_ptr<Entity> Fish::GetCard()
{
	return m_card;
}

void Fish::HuntBait(float const t, Bait& bait)
{
	if (bait.GetBaitSize() == Size::Large && GetSize() == Size::Small)
	{
		return;
	}

	sf::Vector2f delta = GetImage().getPosition() - bait.GetImage().getPosition();
	const float distanceToBait = std::hypot(delta.x, delta.y);

	auto fish = bait.GetFish();
	bool canEatFish = fish != nullptr && !fish->IsEaten() && fish->GetSize() < GetSize() && fish->GetSize() == Size::Small;
	if (distanceToBait < m_sence && (!bait.IsHidden() || canEatFish) && bait.GetImage().getPosition().y > WATER_Y)
	{
		float angleToBait = ToDegrees(std::atan2(delta.y, delta.x));
		m_swimmingStrategy.SetMaxSpeed();
		GetImage().setRotation(angleToBait);
	}

	if (distanceToBait > BAIT_ATTRACTION || (bait.IsHidden() && !canEatFish))
	{
		return;
	}

	if (canEatFish)
	{
		fish->Eat();
	}
	else
	{
		GetImage().setPosition(bait.GetImage().getPosition());
		m_caught = true;
		bait.Eat(this);

		if (bait.GetBaitSize() < GetSize())
		{
			bait.BreakLine();
		}
	}
}

void Fish::Fight(float const t, Bait& bait)
{
	GetImage().setPosition(bait.GetImage().getPosition());

	float baitAngle = ToDegrees(bait.GetAngle());
	float fishRotation = GetImage().getRotation();
	float delta = fishRotation - baitAngle;

	if (GetImage().getPosition().y < WATER_Y)
	{
		m_stamina = 0;
	}

	if (m_tired || m_eaten)
	{
		if (std::abs(delta) > 2)
		{
			GetImage().rotate((delta) > 0 ? -m_rotationSpeed * t : m_rotationSpeed * t);
		}
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
