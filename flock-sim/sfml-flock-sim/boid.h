#pragma once

#include "game.h"

class Boid
{
public:
	Boid();
	~Boid();

	std::vector<Boid>* flock; // the flock this boid belongs to

	sf::Vector2f position; // current position
	sf::Vector2f velocity; // 

	float width = 800; // move to game?
	float height = 800;

	float max_range = 90; // move to flock?
	float min_spacing = 20;
	float max_speed = 2;

	sf::Vector2f Cohesion(std::vector<Boid>& in_range); // return vector toward avg loc of max_range boids
	sf::Vector2f Separation(std::vector<Boid>& in_range); // return vector away from min_range boids
	sf::Vector2f Alignment(std::vector<Boid>& in_range); // return vector avg velocity of max_range boids

	std::vector<Boid> GetInRange(const std::vector<Boid>& v, float r) const; // returns boids from v within r range
	float Magnitude(const sf::Vector2f v) const; // returns the magnitude of v
	float Distance(const sf::Vector2f v) const; // returns distance between this vector and v
	void Normalize(sf::Vector2f& v);
	void WrapWindow(); // moves boids that leave the window bounds to the opposite side of the window
	void Update();
};
