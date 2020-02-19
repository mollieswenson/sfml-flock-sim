#pragma once

#include "boid.h"

class Boid;

class Flock
{
public:
	Flock(int);
	~Flock();

	std::vector<Boid> collection; // vector of all boids in this Flock
	
	void Update(); // update all boids in the collection vector
};
