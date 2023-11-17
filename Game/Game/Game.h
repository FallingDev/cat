#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Cat.h"
#include "Entity.h"

class Game
{
public:
	explicit Game(sf::ContextSettings const& settings);
	void Run();

private:
	void Init();
	void PollEvents();
	void Update();
	void Draw();
	void OnKeyPressed(sf::Event const& event);
	void OnMousePressed();
	void OnMouseReleased();

private:
	sf::Clock m_clock;
	sf::Vector2u m_size;
	sf::RenderWindow m_window;
	Entity m_background = Entity("background.png");
	Entity m_coast = Entity("coast.png");
	Entity m_water = Entity("water.png");
	Bait m_bait;
	Cat m_cat = Cat(m_bait);
	float m_t = 0;
};
