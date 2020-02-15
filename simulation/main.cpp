#include <stdio.h>

#include "game.h"
#include "box2d_hello_world.h"

int main()
{
	//box2d_hello();

	Game simulation;
	simulation.Run();

	//sf::RenderWindow window(sf::VideoMode(800, 800), "Switch Type Test");



	//sf::CircleShape shape1;
	//sf::CircleShape shape2;
 //   sf::CircleShape shape3;

	//shape1.setRadius(3.f);
	//shape2.setRadius(3.f);
	//shape3.setRadius(3.f);

	//shape1.setFillColor(sf::Color::Red);
	//shape2.setFillColor(sf::Color::Green);
	//shape3.setFillColor(sf::Color::Blue);

	//b2Vec2 boid1(10.0f, 10.0f);
	//b2Vec2 boid2(30.0f, 30.0f);
	//b2Vec2 boid3(50.0f, 50.0f);

	//shape1.setPosition(boid1.x, boid1.y);
	//shape2.setPosition(boid2.x, boid2.y);
	//shape3.setPosition(boid3.x, boid3.y);



	////int num = 300;
	////Flock birds(num);

	////std::vector<sf::CircleShape> shapes(num); // create the shapes
	////for (int i = 0; i < num; i++)
	////{
	////	shapes[i].setRadius(3.f);
	////	shapes[i].setFillColor(sf::Color::Green);
	////}

	//while (window.isOpen())
	//{
	//	//birds.Update();

	//	window.clear(sf::Color::Black);

	//	window.draw(shape1);
	//	window.draw(shape2);
	//	window.draw(shape3);

	//	//for (int i = 0; i < num; i++)
	//	//{
	//	//	//shapes[i].setPosition(birds.flock[i].position);
	//	//	//window.draw(shapes[i]);
	//	//}

	//	window.display();

	//	sf::Event event; // event loop
	//	while (window.pollEvent(event))
	//	{
	//		switch (event.type)
	//		{
	//		case sf::Event::Closed:
	//		case sf::Event::KeyPressed:
	//			window.close();
	//			break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	return 0;
}
