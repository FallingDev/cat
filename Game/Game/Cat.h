#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "Bait.h"
#include "Entity.h"
#include "Money.h"

class Cat final : Entity
{
public:
	explicit Cat(Bait& bait, Money& money);
	void SetPosition(sf::Vector2f const position);
	void Draw(sf::RenderWindow& window);
	void Update(float const t);
	void Cast();
	void Throw();
	sf::Vector2f GetLineStart();
	bool IsCasting() const;

private:
	void UpdateLine();

private:
	Entity m_rod = Entity("rod.png");
	sf::Vector2f m_position;
	sf::Vector2f m_rodSize = {460, 30};
	int m_rodRotationSpeed = 0;
	Bait& m_bait;
	sf::Vertex m_line[2];
	bool m_cast = false;
	bool m_fishSelling = false;
	Money& m_money;
	float m_lineTension = 0;
};

