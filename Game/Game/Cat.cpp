#include "Cat.h"
#include "Entity.h"

Cat::Cat()
{
	m_bait.Get().GetImage().setOrigin(-426, -7);
}

void Cat::SetPosition(sf::Vector2f const position)
{
	m_cat.GetImage().setPosition(position);
	m_rod.GetImage().setPosition(position + sf::Vector2f{ 95, 165 });
	m_bait.Get().GetImage().setPosition(m_rod.GetImage().getPosition());
}

void Cat::Cast()
{
	if (m_rodRotationSpeed == 0)
	{
		m_rodRotationSpeed = ROTATION_SPEED;
	}
}

void Cat::Draw(sf::RenderWindow& window)
{
	m_cat.Draw(window);
	m_rod.Draw(window);
	m_bait.Get().Draw(window);
}

void Cat::Update(float const t)
{
	if (m_rodRotationSpeed != 0)
	{
		m_rod.GetImage().rotate(static_cast<float>(m_rodRotationSpeed) * t);
		m_bait.Get().GetImage().rotate(static_cast<float>(m_rodRotationSpeed) * t);
		auto const angle = m_rod.GetImage().getRotation();
		if (m_rodRotationSpeed < 0 && angle < 180)
		{
			m_rodRotationSpeed = -m_rodRotationSpeed;
		}
		if (m_rodRotationSpeed > 0 && angle < 90)
		{
			m_rodRotationSpeed = 0;
			m_rod.GetImage().setRotation(0);
			m_bait.Get().GetImage().setRotation(0);
		}
	}
}


