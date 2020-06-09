/**
@file main.cpp
*/

/*! \mainpage Entry point to 2D Platformer game
*/

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Scene.h"

using namespace sf;

void main() /** Entry point for the application */
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "2D Platformer"); // Open main window

	// The actual game - creates a scene with objects
	Game game;

	// Glorious 60 FPS
	float fFrameTime = 1.f / 60.f;

	// Start a clock to provide time for the physics
	sf::Clock clock;

	while (window.isOpen())
	{
		// Poll event loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// window closed button pressed
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					game.toggleDebug();
				}
			}
		}

		// Find out how much time has elapsed
		float fElapsedTime = clock.getElapsedTime().asSeconds();
		// If a frame has past then update the physics
		if (fElapsedTime > fFrameTime)
		{
			game.update(fElapsedTime);
			clock.restart();
		}

		// Draw to the screen
		window.clear(Color::White);
		window.draw(game);
		window.display();
	}

}