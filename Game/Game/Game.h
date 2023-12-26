#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "Cat.h"
#include "Entity.h"
#include "Fish.h"
#include "SwimmingStrategy.h"
#include <memory>
#include "Money.h"
#include "Common.h"

int constexpr WIDTH = 1800;
int constexpr HEIGHT = 900;
int constexpr RIGHT_LIMIT = 400;
int constexpr BOTTOM_LIMIT = 400;
int constexpr TOP_LIMIT = 300;

class Game
{
public:
	explicit Game(sf::ContextSettings const& settings);
	void Run();

private:
	void Init();
	void InitFishes();
	void PollEvents();
	void Update();
	void Draw();
	void OnKeyPressed(sf::Event const& event);
	void OnMousePressed();
	void OnMouseReleased();
	void UpdateView();

private:
	sf::Clock m_clock;
	sf::Vector2u m_size;
	sf::RenderWindow m_window;
	Entity m_background = Entity("background.png");
	Entity m_coast = Entity("coast.png");
	Entity m_water = Entity("water.png");
	Bait m_bait;
	float m_t = 0;
	std::vector<std::shared_ptr<Fish>> m_fishes;
	Money m_money = Money(START_MONEY_AMOUNT);
	Cat m_cat = Cat(m_bait, m_money);
	sf::View m_view;
	std::shared_ptr<Entity> m_card = nullptr;
	Entity m_blackout = Entity("blackout.png");
};
