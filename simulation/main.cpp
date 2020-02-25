//#include <stdio.h>

#include <SFML/Window.hpp>

#include "flock.h"

int main()

{
	sf::RenderWindow window(sf::VideoMode(600, 600), "Boids");
	window.setPosition(sf::Vector2i(-700, 50));

	Flock birds(100);

	while (window.isOpen())
	{
		birds.Update();

		window.clear(sf::Color::Black);
		for (int i = 0; i < birds.collection.size(); i++)
		{
			window.draw(birds.collection[i].shape);
		}
			
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
