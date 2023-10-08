#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Entity.h"

class Cat
{
public:
	void SetPosition(sf::Vector2f const position);
	void Draw(sf::RenderWindow& window) const;
	void Update(float const t);
	void Cast();

private:
	const int ROTATION_SPEED = -200;
	Entity m_cat = Entity("cat.png");
	Entity m_rod = Entity("rod.png");
	sf::Vector2f m_position;
	sf::Vector2f m_rodSize = {460, 30};
	int m_rodRotationSpeed = 0;
};

