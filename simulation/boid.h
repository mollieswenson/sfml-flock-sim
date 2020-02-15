#pragma once

#include "game.h"
#include "box2d/box2d.h"

// store velocity as a unit vector and speed as a float, makes max speed calcs easier
// if velocity was a unit vector, then you would have to normalize it


// make flock a reference to the flock object, not a pointer to it. 

// dont allow direct access to flock? what if i write it in such a way that boids can change flock and it wont mess things up? bad practice? 

// use const

// flock obj could have method to get widtyh height (of.. the flock? how is that useful? can we use it to check in bounds?) 


class Boid
{
public:
	Boid();
	~Boid();

	sf::CircleShape shape; // the shape that we'll draw? move? should this be ptr to a shape?

	b2Vec2 b2_pos; // position
	float b2_vel; // velocity as a unit vector

	//Flock& flockRef; // reference to this boid's flock object

	//float coh_range; // range in which apply each
	//float sep_range;
	//float ali_range;


	void init(); // set color, shape, etc. and pos to random location outside of bopunds but less than x

//	b2Vec2 b2_coh(std::vector<Boid>& in_range); // return vector toward avg loc of max_range boids
//	b2Vec2 b2_sep(std::vector<Boid>& in_range); // return vector away from min_range boids
//	b2Vec2 b2_ali(std::vector<Boid>& in_range); // return vector avg velocity of max_range boids
//


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
