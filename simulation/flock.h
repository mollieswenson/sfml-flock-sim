#pragma once

#include "boid.h"

class Boid;


class Flock
{
public:
	Flock(int size)
	{
		for (int i = 0; i < size; i++)
		{
			Boid boid;
			collection.push_back(boid);
		}
	}

	~Flock() {};

	void Update() // update all boids in the collection
	{
		for (unsigned int i = 0; i < collection.size(); i++)
			collection[i].Update(collection);
	}

	std::vector<Boid> collection; // vector of all boids in this Flock
};

