#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Firework.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 

int t = 0;


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1000, height = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    /* Game variables*/
    sf::Clock clock;

    const int maxFireworks = 20;
    std::vector<Firework*> *fireworks;
    fireworks = new std::vector<Firework*> ;
    for (int i = 0; i < maxFireworks; i++) {
        fireworks->push_back(new Firework(width, height));
    }

    bool isPaused = false;
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
           /* Update the scene */


            // Update and draw our game scene here
            for (auto firework : *fireworks){
                firework->update(dt);
                firework->draw(window);
            }
            // Show everything we just drew
            window.display();
       }
    }
    return 0;
}
