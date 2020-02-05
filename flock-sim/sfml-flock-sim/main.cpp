#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>




// https://github.com/OwenMcNaughton/Boids-Sfml

// #include <SFML/System/InputStream.hpp>
#include <SFML/System/FileInputStream.hpp>

#include <thread>
#include <iostream>
#include <cassert> 

#include <vld.h>

int range = 10;



class Bird
{
public:
    sf::Vector2i vector;



    sf::Vector2i neighbors[];
    
    sf::Vector2i* GetNeighbors();
    int GetNeighborCount();

    sf::Vector2i Cohesion(sf::Vector2i neighbors[]);
    sf::Vector2i Separation(sf::Vector2i neighbors[]);
    sf::Vector2i Alignment(sf::Vector2i neighbors[]);

};


sf::Vector2i* Bird::GetNeighbors()
{
    // how to get the number of neighbors so we can make an appropriately sized array?

    int count = GetNeighborCount();
    int* neighbors = new int[count];

    while (true)
    {

    }

    for (int i = 0; i < count; i++)
    {
        // while there is a node in range that we have not added to the array, find the next node and add it to the array
        neighbors[i];
    }
}


int Bird::GetNeighborCount()
{
    return 0;
}



sf::Vector2i Bird::Cohesion(sf::Vector2i neighbors[])
{
    sf::Vector2i vector(0,0);
    return vector;
}

sf::Vector2i Bird::Separation(sf::Vector2i neighbors[])
{
    sf::Vector2i vector(0, 0);
    return vector;
}

sf::Vector2i Bird::Alignment(sf::Vector2i neighbors[])
{
    sf::Vector2i vector(0, 0);
    return vector;
}



int main_soon()
{
    return 0;
}