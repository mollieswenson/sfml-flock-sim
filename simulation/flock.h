#pragma once

#include "boid.h"

class Boid;

class Flock
{
public:
	Flock(int);
	~Flock();

	std::vector<Boid> flock; // vector of all boids in this Flock
	void Update(); // update all boids in this flock
};
