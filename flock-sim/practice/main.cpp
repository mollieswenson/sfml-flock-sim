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

void FooThreadFunc()
{
    // this function is started when thread.launch() is called

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread FOO" << std::endl;
}

void BarThreadFunc(int x)
{
    // this function is started when thread.launch() is called

    for (int i = 0; i < 10; ++i)
        std::cout << "I'm thread BAR" << std::endl;
}


class myStream : public sf::InputStream // Abstract class for custom file input streams.
{
    std::shared_ptr<std::istream> m_source; // should i use std istream for the source? 

public:

    explicit myStream(std::shared_ptr<std::istream> stream) : m_source(stream) {}

    sf::Int64 read(void* data, sf::Int64 size) override
    {
        m_source->read(static_cast<char*>(data), size);

        return m_source->gcount();
    }
    sf::Int64 seek(sf::Int64 position) override
    {
        m_source->seekg(position, m_source->beg);

        return m_source->gcount();
    }
    sf::Int64 tell() override
    {
        return m_source->tellg();
    }
    sf::Int64 getSize() override
    {
        auto curr = m_source->tellg();

        m_source->seekg(0, m_source->end);
        sf::Int64 pos = static_cast<sf::Int64>(m_source->tellg());

        m_source->seekg(curr, m_source->beg);

        return pos;
    }

    bool open(std::string filename) { return true; };

    // read must extract size bytes of data from the stream, and copy them to the supplied data address. 
    // It returns the number of bytes read, or -1 on error.

    // seek must change the current reading position in the stream. 
    // Its position argument is the absolute byte offset to jump to 
    // (so it is relative to the beginning of the data, not to the current position). 
    // It returns the new position, or -1 on error.

    // tell must return the current reading position (in bytes) in the stream, or -1 on error.

    // getSize must return the total size (in bytes) of the data which is contained in the stream, or -1 on error.
  
};

void process(sf::InputStream& stream) {}; // to actually do something with the input

int main()
{
    // WINDOWS
    
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!"); // params are size and title of window , dif btwn RenderWindow and Window? 
 
    window.setPosition(sf::Vector2i(10, 50)); // change the position of the window (relative to the desktop)

    
    window.setSize(sf::Vector2u(640, 480)); // change the size of the window
    // window.setFramerateLimit(60); // call once after creating the window to set a frame rate (don't use w/vsync)
    window.setVerticalSyncEnabled(true); // call once after creating the window to sync frame rate to monitor refresh rate

    // get the size of the window
    sf::Vector2u size = window.getSize();
    unsigned int width = size.x;
    unsigned int height = size.y;

    // create some shapes
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) // run the program as long as the window is open
    {

        // EVENTS
        
        // sf::Event is a union, so only one of its members is valid at a time, the valid member is the one that matches the event type.
        //           e.g. event.key for a KeyPressed event; all members of a union share the same memory space, reading invalid is undefined
        //           

        sf::Event event; // sf::Event instances are filled by the pollEvent (or waitEvent) function of the sf::Window class.
        
        // check all the window's events that were triggered since the last iteration of the loop
        while (window.pollEvent(event)) // event loop
        {                 
            // check the type of the event...
            switch (event.type)
            {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // key pressed
            case sf::Event::KeyPressed:
                window.setPosition(sf::Vector2i(100, 500));

                if (event.key.code == sf::Keyboard::Escape) // react to specific key press (for movement, set/clear a bool on key press/release, then move based on bool val)
                    window.close();
                break;

                // key released
            case sf::Event::KeyReleased:
                window.setPosition(sf::Vector2i(10, 50));
                break;

            case sf::Event::MouseWheelScrolled:
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    std::cout << "wheel type: vertical" << std::endl;
                else if (event.mouseWheelScroll.wheel == sf::Mouse::HorizontalWheel)
                    std::cout << "wheel type: horizontal" << std::endl;
                else
                    std::cout << "wheel type: unknown" << std::endl;

                std::cout << "wheel movement: " << event.mouseWheelScroll.delta << std::endl;
                std::cout << "mouse x: " << event.mouseWheelScroll.x << std::endl;
                std::cout << "mouse y: " << event.mouseWheelScroll.y << std::endl;
                break;

                // window reszie
            case sf::Event::Resized:
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                }
                break;

            case sf::Event::MouseMoved:
                std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
                std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
                break;

                // we don't process other types of events
            default:
                break;
            }
        }

        window.clear();
        window.draw(shape);
        window.display();



        // THREADS

        std::thread first(FooThreadFunc);     // spawn new thread that calls foo() as entry point (can call by ref like &FooThreadFunc ?)
        std::thread second(BarThreadFunc, 0);  // spawn new thread that calls bar(0)
        std::cout << "main, foo and bar now execute concurrently...\n";

        // synchronize threads:
        first.join();                // pauses until first finishes
        second.join();               // pauses until second finishes

        std::cout << "foo and bar completed.\n";

        // look at std::mutex lock/trylock to ensure multiple threads don't operate on the same data at once


        // STREAMS SFML provides its own stream interface, which is simpler than std::stream
        //         You must implent all four functions in the InputStream class (read, seek, tell, getSize)

        // resource classes like sf::Texture and sf::SoundBuffer provide loadFromFile and loadFromMemory functions, which read data from conventional sources

        std::shared_ptr<std::istream> customStr; // using a custom stream and std::istream to open an image
        myStream GetStuff(customStr);
        GetStuff.open("image.png");

        sf::FileInputStream stream; // using sf's file input (class is a specialization of InputStream that reads from a file on disk)
        stream.open("image.png");

        if (stream.open("image.png")) // define a function to do something with the input
            process(stream);





        // CLOCK

        sf::Clock clock; // start the clock

         // do some stuff
        sf::Time time_elapsed = clock.getElapsedTime();
        std::cout << time_elapsed.asSeconds() << std::endl;
        
        sf::Time elapsed = clock.restart();  // restart clock (next frame?) also returns elapsed time so you don't have to call getElapsedTime before it
        // updateGame(elapsed); update game logic with elapsed time


        
    }

    return 0;
}