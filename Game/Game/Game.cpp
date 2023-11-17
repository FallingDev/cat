#include "Game.h"
#include <SFML/Window/Event.hpp>

Game::Game(sf::ContextSettings const& settings)
	: m_window(sf::VideoMode(1800, 900), "Cat goes fishing", sf::Style::Default, settings)
{
	Init();
}

void Game::Init()
{
	m_window.setVerticalSyncEnabled(true);
	m_size = m_window.getSize();
	m_coast.GetImage().setPosition({ 0, 400 });
	m_water.GetImage().setPosition({ 0, 590 });
	m_cat.SetPosition({ m_coast.GetSize().x - 230, m_coast.GetImage().getPosition().y - 130 });
	m_bait.SetOriginCenter();
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
		m_bait.Reel(m_t);
	}
}

void Game::Draw()
{
	m_window.clear(sf::Color::Black);
	m_background.Draw(m_window);
	m_water.Draw(m_window);
	m_coast.Draw(m_window);
	m_cat.Draw(m_window);
	m_window.display();
}


