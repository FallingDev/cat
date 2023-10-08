#include "Cat.h"
#include "Entity.h"

void Cat::SetPosition(sf::Vector2f const position)
{
	m_cat.SetPosition(position);
	m_rod.SetPosition(position + sf::Vector2f{ 95, 165 });
}

void Cat::Cast()
{
	if (m_rodRotationSpeed == 0)
	{
		m_rodRotationSpeed = ROTATION_SPEED;
	}
}

void Cat::Draw(sf::RenderWindow& window) const
{
	m_cat.Draw(window);
	m_rod.Draw(window);
}

void Cat::Update(float const t)
{
	if (m_rodRotationSpeed != 0)
	{
		m_rod.Rotate(t * m_rodRotationSpeed);
		auto const angle = m_rod.GetImage().getRotation();
		if (m_rodRotationSpeed < 0 && angle < 180)
		{
			m_rodRotationSpeed = -m_rodRotationSpeed;
		}
		if (m_rodRotationSpeed > 0 && angle > 340)
		{
			m_rodRotationSpeed = 0;
		}
	}
}


