#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Common.h"

Game::Game(sf::ContextSettings const& settings)
	: m_window(sf::VideoMode(WIDTH, HEIGHT), "Cat goes fishing", sf::Style::Default, settings)
{
	Init();
}

void Game::Init()
{
	m_window.setVerticalSyncEnabled(true);
	m_size = m_window.getSize();
	m_view.setSize(m_size.x, m_size.y);
	m_view.setCenter(m_size.x / 2, m_size.y / 2);
	m_coast.GetImage().setPosition({ 0, 400 });
	m_water.GetImage().setPosition({ 0, 590 });
	m_cat.SetPosition({ m_coast.GetSize().x - 230, m_coast.GetImage().getPosition().y - 130 });
	m_bait.SetOriginCenter();
	InitFishes();
}

void Game::InitFishes()
{
	sf::FloatRect standardArea(m_coast.GetImage().getPosition().x + m_coast.GetSize().x, m_water.GetImage().getPosition().y, CUDDLEFISH_AREA.x, CUDDLEFISH_AREA.y);
	for (int i = 0; i < FISHES.CUDDLEFISH; ++i)
	{
		m_fishes.push_back(std::make_shared<Fish>("cuddlefish.png", standardArea));
	}
}

void Game::Run()
{
	while (m_window.isOpen())
	{
		m_t = m_clock.restart().asSeconds();
		PollEvents();
		Update();
		Draw();
	}
}

void Game::OnKeyPressed(sf::Event const& event)
{
	if (event.key.code == sf::Keyboard::Escape)
	{
		m_window.close();
	}
}

void Game::OnMousePressed()
{
	if (!m_bait.IsThrown())
	{
		m_cat.Cast();
	}
}

void Game::OnMouseReleased()
{
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_bait.IsThrown())
	{
		m_cat.Throw();
	}
}

void Game::PollEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			OnKeyPressed(event);
			break;
		case sf::Event::MouseButtonPressed:
			OnMousePressed();
			break;
		case sf::Event::MouseButtonReleased:
			OnMouseReleased();
			break;
		default: break;
		}
	}
}

void Game::Update()
{
	if (m_bait.GetImage().getPosition().y > m_water.GetImage().getPosition().y)
	{
		m_bait.Sink(m_cat.GetLineStart());
	}

	m_cat.Update(m_t);
	m_bait.Update(m_t);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		m_bait.Reel(m_t, m_budget);
	}

	for (auto& fish : m_fishes)
	{
		fish->Update(m_t, m_bait);
	}

	UpdateView();
}

void Game::DrawBudget()
{
	sf::Text text;
	text.setString("$" + std::to_string(m_budget));
	sf::Font font;
	font.loadFromFile("fonts/Kanit-bold.ttf");
	text.setFont(font);
	text.setCharacterSize(50);
	text.setPosition(m_size.x - 300, 30);
	text.setFillColor(sf::Color(64, 72, 86));
	m_window.draw(text);
}

void Game::UpdateView()
{
	sf::Vector2f viewCenter = m_view.getCenter();
	sf::Vector2f delta = { 0, 0 };

	if (!m_bait.IsThrown())
	{
		int speed = -200;
		if (viewCenter.x - m_size.x / 2 > 3)
		{
			delta.x = speed * m_t;
		}
		if (viewCenter.y - m_size.y / 2 > 3)
		{
			delta.y = speed * m_t;
		}
		m_background.GetImage().move(delta);
		m_view.move(delta);
		return;
	}
	
	sf::Vector2f baitPos = m_bait.GetImage().getPosition();
	float rightBound = viewCenter.x - m_size.x / 2 + m_size.x - RIGHT_LIMIT;
	if (baitPos.x > rightBound)
	{
		delta = { baitPos.x - rightBound, 0 };
	}

	float leftBound = viewCenter.x;
	if (m_bait.IsInWater() && baitPos.x < leftBound)
	{
		delta = { baitPos.x - leftBound, 0 };
	}

	float bottomBound = viewCenter.y - m_size.y / 2 + m_size.y - BOTTOM_LIMIT;
	if (baitPos.y > bottomBound)
	{
		delta = { 0, baitPos.y - bottomBound };
	}

	float topBound = viewCenter.y - m_size.y / 2 + TOP_LIMIT;
	if (m_bait.IsInWater() && baitPos.y < topBound)
	{
		delta = { 0, baitPos.y - topBound };
	}

	m_background.GetImage().move(delta);
	m_view.move(delta);
}

void Game::Draw()
{
	m_window.setView(m_view);
	m_window.clear(sf::Color::Black);
	m_background.Draw(m_window);
	m_water.Draw(m_window);
	m_coast.Draw(m_window);
	m_cat.Draw(m_window);
	DrawBudget();
	for (auto& fish : m_fishes)
	{
		fish->Draw(m_window);
	}

	m_window.display();
}


