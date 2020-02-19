#include "flock.h"
#include <iostream>

Flock::Flock(int size)
{                      
	// always add some colored boids so i can identify individuals on screen for debugging

	Boid Green;
	Green.id = "Green";
	Green.shape.setOutlineColor(sf::Color::Green);

	Boid Yellow;
	Yellow.id = "Yellow";
	Yellow.shape.setOutlineColor(sf::Color::Yellow);

	Boid Cyan;
	Cyan.id = "Cyan";
	Cyan.shape.setOutlineColor(sf::Color::Cyan);

	Boid Blue;
	Blue.id = "Blue";
	Blue.shape.setOutlineColor(sf::Color::Blue);

	Boid Magenta;
	Magenta.id = "Magenta";
	Magenta.shape.setOutlineColor(sf::Color::Magenta);

	collection.push_back(Green);
	collection.push_back(Yellow);
	collection.push_back(Cyan);
	collection.push_back(Blue);
	collection.push_back(Magenta);

	for (int i = 0; i < size; i++)
	{
		Boid boid;
		boid.id = i;

		collection.push_back(boid);
	}
}

Flock::~Flock() {}

void Flock::Update()
{
	for (unsigned int i = 0; i < collection.size(); i++)
		collection[i].Update(collection);
}
