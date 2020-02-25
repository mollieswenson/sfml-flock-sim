#include "boid.h"

#include <random>

sf::Color rand_rgb(); // get a random brightly-colored rgb value

Boid::Boid() { Init(); }
Boid::~Boid() {}


void Boid::Update(std::vector<Boid>& collection)
{
	Vec separation = Separation(collection);
	Vec alignment = Alignment(collection);
	Vec cohesion = Cohesion(collection);

	ApplyForce(separation);
	ApplyForce(alignment);
    ApplyForce(cohesion);

	vel += acc;
	vel.Limit(max_speed);
	pos += vel;

	KeepInBounds();
	SetShapePosRot();

	acc.SetZero();
};


Vec Boid::Alignment(std::vector<Boid>& group) const
{
	float neighbor_dist = radius * 20;

	Vec sum(0, 0);
	size_t count = 0;
	
	for (auto&& other : group) 
	{
		float dist = pos.Distance(other.pos);
		if ((dist < neighbor_dist) && (dist > 0))
		{
			sum += other.vel; // sum in-range neighbor velocities
			count++;
		}
	}

	if (count > 0)
	{
		sum.Divide(count); // average neighbor velocity

		sum.Normalize();   // to unit
		sum *= max_speed;  // scale

		Vec steer(sum.x - vel.x, sum.y - vel.y); // point in dir of average vel
		steer.Limit(max_force);

		return steer;
	}

	return sum;
}


Vec Boid::Separation(std::vector<Boid>& group) const
{ 
	float desired_separation = radius * 8;

	Vec sum(0, 0);
	size_t count = 0;

	for (auto&& other : group)
	{
		float dist = pos.Distance(other.pos);
		if ((dist < desired_separation) && (dist > 0))
		{
			Vec offset(pos.x - other.pos.x, pos.y - other.pos.y); // position diff

			offset.Normalize();
			offset.Divide(dist); // to scale force we'll get from this (?)

			sum += offset; // sum offsets of neighbors that are too close
			count++;	
		}
	}

	if (count > 0)
	{
		sum.Divide(count); // average offset of too-close neighbors

		sum.Normalize();   // to unit
		sum *= max_speed;  // scale

		Vec steer(sum.x - vel.x, sum.y - vel.y); // point away from average pos
		steer.Limit(max_force);
		return steer;
	}

	return sum;
}


Vec Boid::Cohesion(std::vector<Boid>& group)
{
	float neighbor_dist = radius * 10;

	Vec sum(0, 0);
	size_t count = 0;

	for (auto&& other : group)
	{
		float dist = pos.Distance(other.pos);
		if ((dist < neighbor_dist) && (dist > 0))
		{
			sum += other.pos; // sum in-range neighbor positions
			count++;
		}
	}

	if (count > 0)
	{
		sum.Divide(count);  // average neighbor position

		Vec steer(sum.x - pos.x, sum.y - pos.y); // points toward average pos

		steer.Normalize();  // to unit
		steer *= max_speed; // scale

		steer -= vel; // get combined force toward target
		steer.Limit(max_force);
		return steer;
	}

	return sum;
}


void Boid::ApplyForce(Vec force)
{
	force *= (1 / mass); // reduce force proportionate to mass
	acc += force;
}


void Boid::SetShapePosRot()
{
	const float pi = 3.14;
	float angle = 0;

	if (vel.Length() == 0)
		return;

	if (vel.y <= 0) 
		angle = asin(vel.x / vel.Length()) * 180.f / pi;
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


void Boid::KeepInBounds()
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

	pos.x = vel.x = in_bounds_x(eng);
	pos.y = vel.y = in_bounds_y(eng);

	vel.Limit(max_speed); // scale to max speed

	shape.setPointCount(3);
	shape.setPoint(0, sf::Vector2f(radius, 0));
	shape.setPoint(1, sf::Vector2f(radius * 0.5, radius * 1.866));
	shape.setPoint(2, sf::Vector2f(radius * 1.5, radius * 1.866));

	shape.setOrigin(radius, radius);

	shape.setOutlineThickness(1);
	shape.setFillColor(sf::Color::Transparent);

	sf::Color color = rand_rgb();
	shape.setOutlineColor(color);
}


sf::Color rand_rgb() 
{
	std::vector<int> rgb{ 0,1,2 };

	int n0{ rand() % 3 }, n1{ rand() % 3 }, n2{ rand() % 3 };

	while (n1 == n0)
		n1 = rand() % 3;
	while (n2 == n0 || n2 == n1)
		n2 = rand() % 3;

	rgb[n0] = 255;
	rgb[n1] = 0;
	rgb[n2] = rand() % 256;

	return sf::Color(rgb[0], rgb[1], rgb[2], 255);
}
