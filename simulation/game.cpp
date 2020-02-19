#include "game.h"
#include <iostream>

Game::Game() {}
Game::~Game() {}

int Game::Run()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Boids");

	Flock birds(40);

	while (window.isOpen())
	{
		birds.Update();

		window.clear(sf::Color::Black);

		for (int i = 0; i < birds.collection.size(); i++)
			window.draw(birds.collection[i].shape);
			
		window.display();

		sf::Event event; // event loop
		while (window.pollEvent(event)) 
		{
			switch (event.type)
			{
			case sf::Event::Closed:
			case sf::Event::KeyPressed:
				window.close();
				break;
			default:
				break;
			}
		}
	}

	return 0;
}
