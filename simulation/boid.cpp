#include <iostream>
#include "boid.h"

Boid::Boid() { Init(); }
Boid::~Boid() {}

void Boid::Update(std::vector<Boid>& collection)
{
	std::cout << "\n\n vel " << vel.x << " " << vel.y;
	// apply the three rules
	Vec separation = Separation(collection);
	Vec alignment = Alignment(collection);
	Vec cohesion = Cohesion(collection);
	
	//separation *= sep_weight;
	//alignment *= ali_weight;
	//cohesion *= coh_weight;  // apply weights

	ApplyForce(separation);
	//ApplyForce(alignment);
	//ApplyForce(cohesion);

	vel += acc;
	//vel.Limit(max_speed);

	vel *= max_speed; // limit speed
	
	pos += vel;

	Bounds();
	SetShape();

	acc.SetZero();

	std::cout << "\n vel " << vel.x << " " << vel.y;

}; // velocity shouldn't stop.. 


Vec Boid::Separation(std::vector<Boid>& group)
{ 
	Vec steer(0, 0);
	Vec difference(0,0);
	float count = 0;

	for (auto&& other : group)
	{
		if ((pos.Distance(other.pos) < sep_distance) && (&other != this)) // too close
		{
			difference = pos;
			difference -= other.pos;
			difference.Normalize();
			steer += difference;
			count++;	
		}
	}

	if (count > 0)
	{
		steer.Divide(count); // average
		//steer.Normalize();// ?? 
		steer *= max_speed; // scale to max

		steer -= vel; // this pos - other pos
		steer.Limit(max_force);

		//ApplyForce(steer); // calc accel
	}

	return steer;
}


Vec Boid::Alignment(std::vector<Boid>& group)
{
	Vec steer;
	float count = 0;

	for (auto&& neighbor : group)
	{
		if ((pos.Distance(neighbor.pos) < ali_distance) && (&neighbor != this))
		{
			steer += neighbor.vel;
			count++;
		}
	}

	if (count > 0)
	{
		steer.Divide(count); // average
		steer.Normalize();

		steer *= max_speed; // scale to max
		steer -= vel; 

		steer.Limit(max_force);
	}

	return steer;
}


Vec Boid::Cohesion(std::vector<Boid>& group)
{
	Vec steer(0, 0);
	float count = 0;

	for (auto&& neighbor : group)
	{
		if ((pos.Distance(neighbor.pos) < coh_range) && (&neighbor != this))
		{
			steer += neighbor.pos;
			count++;
		}
	}

	if (count > 0)
	{
		steer.Divide(count);
		return Seek(steer); // this doesnt do anything
	}

	return steer;
}


Vec Boid::Seek(Vec target)
{
	Vec steer = target;
	steer -= pos;

	steer.Normalize();
	steer *= max_speed;

	steer -= vel;
	steer.Limit(max_force);
	return steer;
}

void Boid::ApplyForce(Vec force)
{
	//Vec f = force; // do i need a new vector here or can i use force? 
	//force *= (1 / mass); // div by mass
	acc += force;
}

float Mag(const b2Vec2& v)
{
	return sqrt(v.x * v.x + v.y * v.y);
}

void Boid::SetShape() // float theta = velocity.heading() + PI/2;
{
	const float pi = 3.14;
	float angle = 0;

	if (vel.Length() == 0)
	{
		return;
	}


	if (vel.y <= 0) 
		angle = asin(vel.x / vel.Length()) * 180.f / pi; // broken!
	else 
		if (vel.x == 0)
			angle = 180.f;
		else if (vel.x > 0) 
			angle = atan(vel.y / vel.x) * 180.f / pi + 90.f;
		else if (vel.x < 0)
			angle = atan(vel.y / vel.x) * 180.f / pi - 90.f;

	shape.setPosition(pos.x, pos.y);
	shape.setRotation(angle);
}

void Boid::Bounds()
{
	if (pos.x > bound_x)
		pos.x = 0;
	else if (pos.x < 0)
		pos.x = bound_x;

	if (pos.y > bound_y)
		pos.y = 0;
	else if (pos.y < 0)
		pos.y = bound_y;
}

void Boid::Init()
{
	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_int_distribution<> in_bounds_x(10, bound_y - 10);
	std::uniform_int_distribution<> in_bounds_y(10, bound_x - 10);
	pos = Vec(in_bounds_x(eng), in_bounds_y(eng));

	std::uniform_int_distribution<> vel_x(.01, max_speed);
	std::uniform_int_distribution<> vel_y(.01, max_speed);
	vel = Vec(vel_x(eng), vel_y(eng));



	float radius = 10;
	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(radius, 0));
	shape.setPoint(1, sf::Vector2f(radius * 0.5, radius * 1.866));
	shape.setPoint(2, sf::Vector2f(radius * 1.5, radius * 1.866));

	shape.setOrigin(radius, radius);

	shape.setOutlineThickness(1);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Green);
}