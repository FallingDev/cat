#include "Game.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "CuddleFish.h"
#include "MustardFish.h"
#include "CowFish.h"
#include "Brimble.h"
#include "Shark.h"
#include "SnobFish.h"
#include "Grumper.h"
#include "Trumble.h"
#include "PinkKisser.h"

Game::Game(sf::ContextSettings const& settings)
	: m_window(sf::VideoMode(WIDTH, HEIGHT), "Cat goes fishing", sf::Style::Fullscreen, settings)
{
	Init();
}

void Game::Init()
{
	m_window.setVerticalSyncEnabled(true);
	m_size = m_window.getSize();
	m_view.setSize(m_size.x, m_size.y);
	m_view.setCenter(m_size.x / 2, m_size.y / 2);
	m_coast.GetImage().setPosition({ -2, COAST_Y });
	m_water.GetImage().setPosition({ 0, WATER_Y });
	m_blackout.GetImage().setPosition({ 0, WATER_Y + 100 });
	m_cat.SetPosition({ m_coast.GetSize().x - 230, m_coast.GetImage().getPosition().y - 130 });
	m_bait.SetOriginCenter();
	m_money.GetImage().setPosition(m_size.x - 300, 30);
	InitFishes();
}

void Game::InitFishes()
{
	sf::Vector2f startPosition = sf::Vector2f{ m_coast.GetSize().x, WATER_Y };
	sf::FloatRect fullArea(startPosition + sf::Vector2f{0, 20}, FULL_AREA);
	sf::FloatRect cuddlefishArea(startPosition + sf::Vector2f{0, 20}, CUDDLEFISH_AREA);
	sf::FloatRect mustardfishArea(startPosition + sf::Vector2f{0, 100}, MUSTARDFISH_AREA);
	sf::FloatRect cowfishArea(startPosition + sf::Vector2f{0, 2000}, COWFISH_AREA);
	sf::FloatRect brimbleArea(startPosition + sf::Vector2f{0, 3000}, BRIMBLE_AREA);
	sf::FloatRect sharkArea(startPosition + sf::Vector2f{0, 3000}, SHARK_AREA);
	sf::FloatRect snobfishArea(startPosition + sf::Vector2f{0, 20}, SNOBFISH_AREA);
	sf::FloatRect grumperArea(startPosition + sf::Vector2f{0, 20}, GRUMPER_AREA);
	sf::FloatRect trumbleArea(startPosition + sf::Vector2f{1500, 2000}, TRUMBLE_AREA);
	sf::FloatRect pinkKisserArea(startPosition + sf::Vector2f{1500, 1000}, PINK_KISSER_AREA);

	for (int i = 0; i < FISHES.CUDDLEFISH; ++i)
	{
		m_fishes.push_back(std::make_shared<CuddleFish>(cuddlefishArea));
	}
	for (int i = 0; i < FISHES.CUDDLEFISH_FULL; ++i)
	{
		m_fishes.push_back(std::make_shared<CuddleFish>(fullArea));
	}
	for (int i = 0; i < FISHES.MUSTARDFISH; ++i)
	{
		m_fishes.push_back(std::make_shared<MustardFish>(mustardfishArea));
	}
	for (int i = 0; i < FISHES.COWFISH; ++i)
	{
		m_fishes.push_back(std::make_shared<CowFish>(cowfishArea));
	}
	for (int i = 0; i < FISHES.BRIMBLE; ++i)
	{
		m_fishes.push_back(std::make_shared<Brimble>(brimbleArea));
	}
	for (int i = 0; i < FISHES.SHARK; ++i)
	{
		m_fishes.push_back(std::make_shared<Shark>(sharkArea));
	}
	for (int i = 0; i < FISHES.SNOBFISH; ++i)
	{
		m_fishes.push_back(std::make_shared<SnobFish>(snobfishArea));
	}
	for (int i = 0; i < FISHES.GRUMPER; ++i)
	{
		m_fishes.push_back(std::make_shared<Grumper>(grumperArea));
	}
	for (int i = 0; i < FISHES.TRUMBLE; ++i)
	{
		m_fishes.push_back(std::make_shared<Trumble>(trumbleArea));
	}
	for (int i = 0; i < FISHES.PINK_KISSER; ++i)
	{
		m_fishes.push_back(std::make_shared<PinkKisser>(pinkKisserArea));
	}
}

void Game::Run()
{
	while (m_window.isOpen())
	{
		m_t = m_clock.restart().asSeconds();
		if (m_t < 1)
		{
			PollEvents();
			Update();
			Draw();
		}
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
	m_card = nullptr;
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

	for (auto& fish : m_fishes)
	{
		fish->Update(m_t, m_bait);
	}

	UpdateView();
}

void Game::UpdateView()
{
	sf::Vector2f viewCenter = m_view.getCenter();
	sf::Vector2f delta = { 0, 0 };

	if (!m_bait.IsThrown())
	{
		auto fish = m_bait.GetFish();
		if (m_card == nullptr && fish != nullptr && !fish->IsEaten() && !m_cat.IsCasting())
		{
			m_card = fish->GetCard();
		}

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
		m_money.GetImage().move(delta);
		return;
	}
	
	sf::Vector2f baitPos = m_bait.GetImage().getPosition();
	float rightBound = viewCenter.x - m_size.x / 2 + m_size.x - RIGHT_LIMIT;
	if (baitPos.x > rightBound)
	{
		delta += { baitPos.x - rightBound, 0 };
	}

	float leftBound = viewCenter.x;
	if (m_bait.IsInWater() && baitPos.x < leftBound && viewCenter.x + m_size.x / 2 < m_water.GetSize().x)
	{
		delta += { baitPos.x - leftBound, 0 };
	}

	float bottomBound = viewCenter.y - m_size.y / 2 + m_size.y - BOTTOM_LIMIT;
	if (baitPos.y > bottomBound && viewCenter.y + m_size.y / 2 < WATER_Y + m_water.GetSize().y)
	{
		delta += { 0, baitPos.y - bottomBound };
	}

	float topBound = viewCenter.y - m_size.y / 2 + TOP_LIMIT;
	if (m_bait.IsInWater() && baitPos.y < topBound)
	{
		delta += { 0, baitPos.y - topBound };
	}

	m_background.GetImage().move(delta);
	m_view.move(delta);
	m_money.GetImage().move(delta);
}

void Game::Draw()
{
	m_window.setView(m_view);
	m_window.clear(sf::Color::Black);
	m_background.Draw(m_window);
	m_water.Draw(m_window);
	m_coast.Draw(m_window);
	m_cat.Draw(m_window);
	m_money.Draw(m_window);
	for (auto& fish : m_fishes)
	{
		fish->Draw(m_window);
	}
	if (m_card != nullptr)
	{
		m_card->Draw(m_window);
	}
	m_blackout.Draw(m_window);

	m_window.display();
}


