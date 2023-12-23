#pragma once
#include "Entity.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class Money : public Entity
{
public:
	Money(const int amount);
	void Add(const int amount);
	void Reduce(const int amount);
	int Get();
	void Draw(sf::RenderWindow& window) override;

private:
	int m_amount;
	sf::Font m_font;
	sf::Text m_text;
};

