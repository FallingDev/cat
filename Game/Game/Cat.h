#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Bait.h"
#include "Entity.h"

class Cat
{
public:
	Cat();
	void SetPosition(sf::Vector2f const position);
	void Draw(sf::RenderWindow& window);
	void Update(float const t);
	void Cast();

private:
	const int ROTATION_SPEED = -300;
	Entity m_cat = Entity("cat.png");
	Entity m_rod = Entity("rod.png");
	sf::Vector2f m_position;
	sf::Vector2f m_rodSize = {460, 30};
	int m_rodRotationSpeed = 0;
	Bait m_bait;
};

