#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Star.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!",sf::Style::Fullscreen, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;


    std::random_device rd;
    std::vector<Star> stars;
   
    const int maxStarsSize = 400;
    for (int i = 0; i < maxStarsSize; i++){
        stars.push_back(Star(window.getSize().x, window.getSize().y, i));
    }

    bool isPaused = false;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        window.clear();

        // Clear everything from the last frame
        /*     
        ****************************************
        Handle the players input
        ****************************************
        */

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
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
            for (int i = 0; i < maxStarsSize; i++) 
                stars[i].update(dt);
                
            // Draw our game scene here

            for (int i = 0; i < maxStarsSize; i++) {
                //window.draw(*stars[i].draw()[0]);
                window.draw(*stars[i].draw()[1]);
            }
                
            // Show everything we just drew
            window.display();
       }
    }

    return 0;
}
