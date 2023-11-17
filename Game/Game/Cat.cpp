#pragma once
#include "Cat.h"
#include "Entity.h"
#include "Common.h"

Cat::Cat(Bait& bait)
	: Entity("cat.png")
	, m_bait(bait)
{
}

void Cat::SetPosition(sf::Vector2f const position)
{
	GetImage().setPosition(position);
	m_rod.GetImage().setPosition(position + sf::Vector2f{ 95, 165 });
	m_bait.GetImage().setPosition(m_rod.GetImage().getPosition() + m_rod.GetSize() + sf::Vector2f{ 0, m_bait.GetSize().y / 2 });
}

void Cat::Cast()
{
	if (m_bait.IsThrown())
	{
		return;
	}
	if (m_rodRotationSpeed == 0)
	{
		m_rodRotationSpeed = CASTING_SPEED;
		m_cast = true;
	}
}

void Cat::Throw()
{
	if (m_cast && m_rodRotationSpeed > 0)
	{
		m_bait.Throw(m_rod.GetImage().getRotation() + 90);
		m_cast = false;
	}
}

sf::Vector2f Cat::GetLineStart()
{
	return sf::Vector2f(m_line[0].position.x, m_line[0].position.y);
}

void Cat::UpdateLine()
{
	auto const angle = m_rod.GetImage().getRotation();
	auto const radians = ToRadians(angle);
	auto const rotationVector = sf::Vector2f{ m_rod.GetSize().x * std::cos(radians), m_rod.GetSize().x * std::sin(radians) };
	m_line[0] = sf::Vertex(m_rod.GetImage().getPosition() + rotationVector + sf::Vector2f{0, m_rod.GetSize().y});
	m_line[1] = sf::Vertex(m_bait.GetImage().getPosition());
	m_line[0].color = sf::Color(200, 200, 200);
	m_line[1].color = sf::Color(200, 200, 200);
}

void Cat::Draw(sf::RenderWindow& window)
{
	UpdateLine();
	Entity::Draw(window);
	window.draw(m_line, 2, sf::Lines);
	m_rod.Draw(window);
	m_bait.Draw(window);
}

void Cat::Update(float const t)
{
	if (m_rodRotationSpeed == 0)
	{
		return;
	}

	m_rod.GetImage().rotate(static_cast<float>(m_rodRotationSpeed) * t);
	auto const angle = m_rod.GetImage().getRotation();
	if (m_rodRotationSpeed < 0 && angle < 180)
	{
		m_rodRotationSpeed = -m_rodRotationSpeed;
	}

	if (m_rodRotationSpeed > 0 && angle < 90)
	{
		m_rodRotationSpeed = 0;
		m_rod.GetImage().setRotation(0);
		m_cast = false;
	}

	if (!m_bait.IsThrown())
	{
		auto const radians = ToRadians(angle);
		auto const rotationVector = sf::Vector2f{ m_rod.GetSize().x * std::cos(radians), m_rod.GetSize().x * std::sin(radians) };
		m_bait.GetImage().setPosition(m_rod.GetImage().getPosition() + sf::Vector2f{ 0, m_rod.GetSize().y } + rotationVector);
	}
}


