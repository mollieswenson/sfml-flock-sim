#pragma once

#include <iostream>
#include <random>
#include <vector>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "box2d/box2d.h"


struct Vec : public b2Vec2 // extend b2Vec2 (how do i fwd declare this?)
{
	Vec() : b2Vec2(0, 0) {}
	Vec(float x, float y) : b2Vec2(x, y) {}
	using b2Vec2::b2Vec2;

	void Limit(float max)
	{
		float size = Length();
		if (size > max)
			Set(x / size, y / size);
	}

	float Distance(const Vec& other) const
	{
		float x(x), y(y);
		x -= other.x;
		y -= other.y;
		return sqrt(x * x + y * y);
	}

	void Divide(float n)
	{
		x /= n;
		y /= n;
	}
};

class Boid
{
public:
	Boid();
	~Boid();

	void Init(); // set color, shape, etc. and pos to random location outside of bopunds but less than x
	void Update(std::vector<Boid>& group);

	Vec Cohesion(std::vector<Boid>& group); // move toward average position
	Vec Separation(std::vector<Boid>& group); // maintain separation distance
	Vec Alignment(std::vector<Boid>& group); // match average heading

	Vec Seek(Vec target); // calculate steering force toward target
	void ApplyForce(Vec force); // apply  force to acceleration

	void SetShape(); // 
	void Bounds();

	float mass = 100;

	sf::ConvexShape shape; // for draw/render

	float bound_x = 800; // screen size
	float bound_y = 800;

	Vec pos{ 0.0f, 0.0f };
	Vec vel{ 0.0f, 0.0f };
	Vec acc{ 0.0f, 0.0f };

	float coh_range = 2000;
	float sep_distance = 50;
	float ali_distance = 50;
	
	float coh_weight = 1;
	float sep_weight = 1.5;
	float ali_weight = .5;
	
	float max_speed = .99; // something wrong here, sometimes they go faster when this is smaller
	float max_force = .1;



	//float Distance(const Vec&) const; // returns distance between this vector and v
	
	//void Limit(Vec&, float f);


	std::string id = ""; // for testing

};
