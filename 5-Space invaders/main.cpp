#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Alien.hpp"
#include "Player.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1920, height =1080 ;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Fullscreen, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;
    sf::Clock turnClock;


    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("resources\\graphics\\spaceInvaders.png");


    int aliensWidth = 11;
    int aliensHeight = 5;
    std::vector<Alien> aliens;

    int i = 0;
    for (int row = 0; row < aliensHeight; row++) {
        for (int column = 0; column < aliensWidth; column++){
            aliens.push_back(Alien(width, height, row, column));
            aliens[i].loadTexture(spriteSheet);
            i++;
        }
    }





    bool isPaused = false;

    int row, col;
    turnClock.restart();
    sf::Vector2f speed(10, 0);
    int delay = 800; 
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        window.clear(sf::Color(15, 15, 15));

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

        if (turnClock.getElapsedTime().asMilliseconds() > delay) {
            
            i = 0;
            for (row = 0; row < aliensHeight; row++) {
                for (col = 0; col < aliensWidth; col++){
                    if (aliens[i].getState() != Alien::State::dead){
                        if ((aliens[i].getPosition().x + speed.x < 10) || (aliens[i].getPosition().x + speed.x > width - aliens[i].getSize().x)) {
                            speed.x = -speed.x;
                            speed.y = aliens[i].getSize().y / 2;
                        }
                    }
                    i++;
                }
            }
            
            

            i = 0;
            for (row = 0; row < aliensHeight; row++) {
                for (col = 0; col < aliensWidth; col++){
                    if (aliens[i].getState() != Alien::State::dead) {
                        aliens[i].update(speed);
                    }
                    //std::cout << speed.x << " " << speed.y << std::endl;
                    i++;
                }
            }
            speed.y = 0;
            turnClock.restart();
        }

        // Show everything we just drew

        i = 0;
        for (row = 0; row < aliensHeight; row++) {
            for (col = 0; col < aliensWidth; col++){
                window.draw(aliens[i]);
                i++;
            }
        }

        window.display();
       }
    }

    return 0;
}
