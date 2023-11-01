#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Bait.h"
#include "Entity.h"

class Cat final : Entity
{
public:
	explicit Cat(Bait& bait);
	void SetPosition(sf::Vector2f const position);
	void Draw(sf::RenderWindow& window);
	void Update(float const t);
	void Cast();
	void Throw();

private:
	void UpdateLine();

private:
	Entity m_rod = Entity("rod.png");
	sf::Vector2f m_position;
	sf::Vector2f m_rodSize = {460, 30};
	int m_rodRotationSpeed = 0;
	Bait& m_bait;
	sf::Vertex m_line[2];
};

