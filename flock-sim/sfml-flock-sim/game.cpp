#include "game.h"

Game::Game() {}
Game::~Game() {}

int Game::Run()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "Boids");

	int num = 300;
	Flock bird(num);

	std::vector<sf::CircleShape> shapes(num); // create the shapes
	for (int i = 0; i < num; i++)
	{
		shapes[i].setRadius(3.f);
		shapes[i].setFillColor(sf::Color::Green);
	}

	while (window.isOpen())
	{
		bird.Update();

		window.clear(sf::Color::Black);

		for (int i = 0; i < num; i++)
		{
			shapes[i].setPosition(bird.flock[i].position);
			window.draw(shapes[i]);
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
