//#include <stdio.h>

#include <SFML/Window.hpp>

#include "flock.h"

int main()

{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Boids");

	Flock birds(200);

	while (window.isOpen())
	{
		birds.Update();

		window.clear(sf::Color::Black);
		for (int i = 0; i < birds.collection.size(); i++)
		{
			birds.collection[i].shape.setFillColor(sf::Color::Cyan);
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
