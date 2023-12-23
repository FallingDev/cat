#include "Money.h"

Money::Money(const int amount)
	: Entity("money.png")
	, m_amount(amount)
{
	m_font.loadFromFile("fonts/Kanit-bold.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
	m_text.setFillColor(sf::Color(64, 72, 86));
	m_text.setString(std::to_string(m_amount));
}

void Money::Add(const int amount)
{
	m_amount += amount;
	m_text.setString(std::to_string(m_amount));
}

void Money::Reduce(const int amount)
{
	m_amount += amount;
	m_text.setString(std::to_string(m_amount));
}

int Money::Get()
{
	return m_amount;
}

void Money::Draw(sf::RenderWindow& window)
{
	Entity::Draw(window);
	m_text.setPosition(GetImage().getPosition().x + GetSize().x + 12, GetImage().getPosition().y - 6);
	window.draw(m_text);
}
