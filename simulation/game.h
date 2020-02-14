#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <vector>

#include "flock.h"

class Game
{
public:
	Game();
	~Game();

	int Run();
};
