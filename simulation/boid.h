#pragma once

#include "game.h"
#include "box2d/box2d.h"

class Boid
{
public:
	Boid();
	~Boid();

	void Init(); // set color, shape, etc. and pos to random location outside of bopunds but less than x

	sf::ConvexShape shape;

	std::string id = ""; // for testing

	float bound_x = 800;
	float bound_y = 600;

	b2Vec2 position = b2Vec2(0,0); // current position
	b2Vec2 velocity = b2Vec2(0,0); // store this as a unit vector? 

	float coh_distance = 25;
	float sep_distance = 20;
	float ali_distance = 70;
	
	float coh_weight = 1.0;
	float sep_weight = .5;
	float ali_weight = 1.5;
	
	float max_speed = .5; // something wrong here, sometimes they go faster when this is smaller
	float max_turn = .5;

	void Cohesion(b2Vec2&, std::vector<Boid>&); // sets cohesion vector toward avg loc of max_range boids
	void Separation(b2Vec2&, std::vector<Boid>&); // sets separation vector away from min_range boids
	void Alignment(b2Vec2&, std::vector<Boid>&); // sets alignment vector avg velocity of max_range boids

	float Magnitude(const b2Vec2&) const; // returns  magnitude
	float Distance(const b2Vec2&) const; // returns distance between this vector and v
	void Update(std::vector<Boid>&);
	void Limit(b2Vec2&, float);
	void SetShape();
	void Bounds();
};
