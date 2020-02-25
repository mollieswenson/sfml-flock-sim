#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "box2d/box2d.h"

struct Vec : public b2Vec2 // extend b2Vec2 (how do i fwd declare Vec?)
{
	using b2Vec2::b2Vec2;
	
	Vec() : b2Vec2(0, 0) {}
	Vec(float x, float y) : b2Vec2(x, y) {}

	float Distance(const Vec& other) const { return Vec(x - other.x, y - other.y).Length(); }
	void Divide(float n) { x /= n; y /= n; }

	void Limit(float max) // limit a force
	{
		float size = Length();
		if (size > max)
			Set(x / size, y / size);
	}
};


class Boid
{
public:
	Boid();
	~Boid();

	void Init(); // set pos, vel, shape, id_tag
	void Update(std::vector<Boid>& group);

	Vec Alignment(std::vector<Boid>& group) const; // match average heading of neighbors
	Vec Separation(std::vector<Boid>& group) const; // maintain distance from neighbors
	Vec Cohesion(std::vector<Boid>& group); // move toward average position of neighbors

	void ApplyForce(Vec force); // apply a force to acceleration

	void SetShapePosRot(); // sets position and rotation of shape
	void KeepInBounds(); // wraps boids that leave the window to the opposite side

	float bound_x = 600; // window size
	float bound_y = 600;

	float radius = 5; // radius of boid, used to calc range for align/separate/cohesion
	float mass = radius * 2; // mass, only used when applying force for now

	float max_speed = 2;
	float max_force = 1;

	Vec pos{ 0.0f, 0.0f }; // current position of boid
	Vec vel{ 0.0f, 0.0f }; // velocity of boid (storing as a unit vector makes things slow down..?)
	Vec acc{ 0.0f, 0.0f }; // acceleration -- resets to 0 each frame

	sf::ConvexShape shape; // shape that gets drawn in window
};
