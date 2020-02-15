#include "boid.h"

// updates
// initially place boids just outside of bounds so they fly in (proportionate to screen size)


Boid::Boid() {}
Boid::~Boid() {}


void Boid::init()
{
	srand(unsigned int(time(NULL)));

	int width = 100;
	int height = 100;

	// in bounds is.. 
	// x is either greater than 0, or less than 100 ( 0 < x < 100) between 1 and 100
	// y is either greater than 0, or less than 100 ( 0 < y < 100) between 1 and 100
	

	// out of bounds is.. 
	// x is either less than 0, or greater than 100 ( 0 > x > 100 ) below 0, above 100
	// y is either less than 0, or greater than 100 ( 0 > y > 100) below 0, above 100

	// out of bounds with max out of bound contstriants is.. 
	// x is either less than 0, greater than -100, or greater than 100, or less than 200 ( 0 > x > -100 || 100 < x < 200 ) between -100 - 0 || 100 - 200
	// y is either less than 0, greater than -100, or greater than 100, or less than 200 ( 0 > y >  100 || 100 < y < 200 ) between -100 - 0 || 100 - 200

	// so we need a random number between either -100 and 0, or 100 and 200, so between -100 and 200, and then cut out 0 - 100
	// so rand number between smallest and larges, then subtract length or width


	// outPut = rand() % ((userEnd - userBeg) + 1) + userBeg;

	// outPut = rand() % ((userEnd - userBeg) + 1) + userBeg;




	b2_pos.x = static_cast <float>(rand() % 100);
	b2_pos.y = static_cast <float>(rand() % 300); // init location

	shape.setRadius(3.f);
    shape.setFillColor(sf::Color::Red); // shape properties
}


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




//
//b2Vec2 Boid::b2_coh(std::vector<Boid>& in_range) // return vector toward avg loc of max_range boids 
//{
//	// use in range for coh.. 
//
//	b2Vec2 center_of_mass;
//
//
//}

//b2Vec2 Boid::b2_sep(std::vector<Boid>& in_range) // return vector away from min_range boids
//{
//	// use in range for 
//}
//
//b2Vec2 Boid::b2_ali(std::vector<Boid>& in_range) // return vector avg velocity of max_range boids
//{
//
//}




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