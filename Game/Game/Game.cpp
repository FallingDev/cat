#include "Game.h"
#include <SFML/Window/Event.hpp>

Game::Game(sf::ContextSettings const& settings)
	: m_window(sf::VideoMode(), "Pointer", sf::Style::Fullscreen, settings)
{
	Init();
}

void Game::Init()
{
	m_window.setVerticalSyncEnabled(true);
	m_size = m_window.getSize();
	m_coast.SetPosition({ 0, 400 });
	m_water.SetPosition({ 0, 590 });
	m_cat.SetPosition({ m_coast.GetSize().x - 230, m_coast.GetPosition().y - 130 });
}

void Game::Run()
{
	while (m_window.isOpen())
	{
		PollEvents();
		Update();
		Draw();
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
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}
			break;
		case sf::Event::MouseButtonPressed:
			m_cat.Cast();
		default: break;
		}
	}
}

void Game::Update()
{
	float const t = m_clock.restart().asSeconds();
	m_cat.Update(t);
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


