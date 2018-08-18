#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Planet.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1920, height = 1080;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Fullscreen, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    /* Game variables*/
    sf::Clock clock;

    srand(time(NULL));

    bool isPaused = false;

    Planet *sun;
    sun = new Planet(width, height);
    sf::Vector2f *parentPos = new sf::Vector2f (width/2 - sun->getRadius(), height/2 - sun->getRadius());
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        window.clear(sf::Color(10, 10, 10));

        // Clear everything from the last frame
        /*     
        ****************************************
        Handle the players input
        ****************************************
        */

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            // we don't process other types of events
            default:
                break;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            if (sun != nullptr) {
                delete sun;
                sun = nullptr;
            }
            window.clear(sf::Color(10, 10, 10));
            sun = new Planet(width, height);
            usleep(80000);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            isPaused = !isPaused;
            usleep(300000);
        }

        /*     
        ****************************************     
        Update the scene :)
        ****************************************     
        */

       if (!isPaused) {

           if (sun != nullptr) {
           /* Update the scene */
            sun->update(dt, *parentPos);
            // Draw our game scene here
            sun->draw(window);
            // Show everything we just drew
            window.display();
           }
       }
    }

    return 0;
}

