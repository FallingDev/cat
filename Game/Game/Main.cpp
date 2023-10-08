#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>

#include "Game.h"

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	Game game(settings);
	game.Run();
	return 0;
}