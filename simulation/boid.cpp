#include <iostream>
#include <random>

#include "boid.h"

// http://www.kfish.org/boids/pseudocode.html
// https://www.oreilly.com/library/view/ai-for-game/0596005555/ch04.html

void Multiply(b2Vec2& v, float f);
void Divide(b2Vec2& v, float f);

Boid::Boid() { Init(); }
Boid::~Boid() {}

void Boid::Init()
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> in_bounds_x(10, bound_y-10);
	std::uniform_int_distribution<> in_bounds_y(10, bound_x-10);
	position = b2Vec2(in_bounds_x(eng), in_bounds_y(eng));

	std::uniform_int_distribution<> vel_x(.01, max_speed);
	std::uniform_int_distribution<> vel_y(.01, max_speed);
	velocity = b2Vec2(vel_x(eng), vel_y(eng));

	float radius = 15;
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(radius, 0));
	shape.setPoint(1, sf::Vector2f(radius * 0.5, radius * 1.866));
	shape.setPoint(2, sf::Vector2f(radius * 1.5, radius * 1.866));

	shape.setOrigin(radius, radius);

	shape.setOutlineThickness(1);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
}


void Boid::Update(std::vector<Boid>& collection)
{
	b2Vec2 cohesion(0,0), separation(0,0), alignment(0,0), acceleration(0,0);

	Cohesion(cohesion, collection); // apply the three rules
	Separation(separation, collection);
	Alignment(alignment, collection);

	cohesion *= coh_weight;  // apply weights
	separation *= sep_weight;
	alignment *= ali_weight;

	acceleration = cohesion + separation + alignment;
	acceleration *= max_speed / 2; // limit acceleration

	velocity += acceleration;
	velocity *= max_speed; // limit speed
	
	position = position + velocity;

	Bounds();
	SetShape();
};


void Boid::Cohesion(b2Vec2& cohesion, std::vector<Boid>& neighbors)
{
	float count = 0;
	for (auto&& neighbor : neighbors)
	{
		float distance = Distance(neighbor.position);

		if ((distance < coh_distance) && (&neighbor != this))
		{
			cohesion += neighbor.position;
			count++;
		}
	}

	if (count > 0)
	{
		Divide(cohesion, count);

		b2Vec2 target(0,0);

		target = target - cohesion; // vector from position to target
		target.Normalize();
		target *= max_speed; // limit speed

		cohesion = target - velocity;
		Limit(cohesion, max_turn); // limit steering
	}
}


void Boid::Separation(b2Vec2& separation, std::vector<Boid>& neighbors)
{ 
	float count = 0;

	for (auto&& neighbor : neighbors) 
	{
		float distance = Distance(neighbor.position);

		if ((distance < sep_distance) && (&neighbor != this)) // too close
		{
			b2Vec2 difference(0, 0);
			difference = position - neighbor.position;
			difference.Normalize();
			Divide(difference, distance); // apply more separation to closer boids
			separation += difference; // i think this might be wrong
			count++;
		}
	}

	if (count > 0)
	{
		Divide(separation, count); 
	}

	if (Magnitude(separation) > 0)
	{
		separation.Normalize();
		separation *= max_speed;
		separation -= velocity;
		Limit(separation, max_turn);
	}
}


void Boid::Alignment(b2Vec2& alignment, std::vector<Boid>& neighbors)
{
	float count = 0;
	for (auto&& neighbor : neighbors)
	{
		float distance = Distance(neighbor.position);
		if ((distance < ali_distance) && (&neighbor != this))
		{
			alignment += neighbor.velocity;
			count++;
		}
	}

	if (count > 0)
	{
		Divide(alignment, count);  // average velocity of in-range boids
		alignment.Normalize();     // alignment to unit vector
		alignment *= max_speed;
		alignment -= velocity;
		Limit(alignment, max_turn);
	}
}


void Boid::SetShape()
{
	const float pi = 3.14;
	float angle = 0;

	if (velocity.y <= 0) 
		angle = asin(velocity.x / Magnitude(velocity)) * 180.f / pi;
	else 
		if (velocity.x == 0)
			angle = 180.f;
		else if (velocity.x > 0) 
			angle = atan(velocity.y / velocity.x) * 180.f / pi + 90.f;
		else if (velocity.x < 0)
			angle = atan(velocity.y / velocity.x) * 180.f / pi - 90.f;

	shape.setPosition(position.x, position.y);
	shape.setRotation(angle);
}


float Boid::Distance(const b2Vec2& other_pos) const
{
	float x = position.x - other_pos.x;
	float y = position.y - other_pos.y;
	return sqrt(x * x + y * y);
}


float Boid::Magnitude(const b2Vec2& v) const
{
	return sqrt(v.x * v.x + v.y * v.y);
}


void Boid::Limit(b2Vec2& v, float max)
{
	float size = Magnitude(v);
	if (size > max)
	{
		v.Set(v.x / size, v.y / size);
	}
}


void Boid::Bounds()
{
	if (position.x > bound_x)
		position.x = 0;
	else if (position.x < 0)
		position.x = bound_x;

	if (position.y > bound_y)
		position.y = 0;
	else if (position.y < 0)
		position.y = bound_y;
}


void Multiply(b2Vec2& v, float f)
{
	v.x *= f;
	v.y *= f;
}


void Divide(b2Vec2& v, float f)
{
	v.x /= f;
	v.y /= f;
}