#include "flock.h"

Flock::Flock(int size)
{                      
	unsigned int time_ui = unsigned int(time(NULL));
	srand(time_ui);

	for (int i = 0; i < size; i++)
	{
		Boid boid;

		boid.flock = &flock;

		float x = static_cast <float>(rand() % 800); // window size
		float y = static_cast <float>(rand() % 800);
		boid.position = sf::Vector2f(x, y);

		x = static_cast <float>(1 + rand() % 100);
		y = static_cast <float>(1 + rand() % 100);
		boid.velocity = sf::Vector2f(x, y);

		flock.push_back(boid);
	}
}

Flock::~Flock() {}

void Flock::Update()
{
	for (int i = 0; i < flock.size(); i++)
		flock[i].Update();
}

