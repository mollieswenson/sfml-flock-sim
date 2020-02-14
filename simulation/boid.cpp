#include "boid.h"

Boid::Boid() {}
Boid::~Boid() {}

void Boid::Update()  // http://www.kfish.org/boids/pseudocode.html
{
	std::vector<Boid> in_range = GetInRange(*flock,  max_range);
	std::vector<Boid> too_close = GetInRange(in_range, min_spacing);

	velocity +=  Cohesion(in_range) + Separation(too_close) + Alignment(in_range);

	if (Magnitude(velocity) > max_speed)  
	{ 
		velocity.x = velocity.x / Magnitude(velocity) * max_speed; // does /= change order of operations? 
		velocity.y = velocity.y / Magnitude(velocity) * max_speed;
	}

	position += velocity;

	WrapWindow();
};

sf::Vector2f Boid::Cohesion(std::vector<Boid>& in_range) 
{
	sf::Vector2f center;

	for (auto&& other : in_range)
		center += other.position;

	center.x /= in_range.size();
	center.y /= in_range.size();

	center -= position;

	center.x /= 100;
	center.y /= 100;

	return center;
}

sf::Vector2f Boid::Separation(std::vector<Boid>& too_close) 
{
	sf::Vector2f distance;
	for (auto&& other : too_close)
	{
		if (Magnitude(position - other.position) < min_spacing)
			distance = position - other.position;
	}

	return distance;
}

sf::Vector2f Boid::Alignment(std::vector<Boid>& in_range) 
{
	sf::Vector2f average;

	for (auto&& other : in_range)
		average += other.velocity;

	average.x /= in_range.size();
	average.y /= in_range.size();

	average -= velocity;

	average.x /= 8;
	average.y /= 8;

	return average;
}

std::vector<Boid> Boid::GetInRange(const std::vector<Boid>& collection, float range) const
{
	std::vector<Boid> in_range;

	for (auto&& other : collection)
	{
		if (&other == this)
			continue;

		if (Distance(other.position) < range)
			in_range.push_back(other);
	}

	return in_range;
}

void Boid::WrapWindow()
{
	if (position.x > width)
		position.x = 0;
	else if (position.x < 0)
		position.x = width;

	if (position.y > height)
		position.y = 0;
	else if (position.y < 0)
 		position.y = height;
}

float Boid::Distance(const sf::Vector2f other_pos) const
{
	float x = position.x - other_pos.x;
	float y = position.y - other_pos.y;
	return sqrt(x * x + y * y);
}

void Boid::Normalize(sf::Vector2f& v)
{
	float mag = Magnitude(v);
	v.x = v.x / mag;
	v.y = v.y / mag;
}

float Boid::Magnitude(const sf::Vector2f v) const
{
	return sqrt(v.x * v.x + v.y * v.y);
}