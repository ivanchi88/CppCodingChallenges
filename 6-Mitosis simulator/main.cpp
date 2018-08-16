#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Cell.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1920, height = 1080;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;

    srand(time(NULL));

    std::random_device rd;
    std::vector<Cell*> *cells = new std::vector<Cell*>();
   
    int numberCells = 10;
    for (int i = 0; i < numberCells; i++){
        cells->push_back(new Cell (width, height));
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
            switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed: {

                sf::Vector2f mousePos;
                mousePos = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                for (auto cell : *cells) {
                    if (cell->containsPoint(&mousePos)){
                        cells->push_back(new Cell(width, height, new sf::Vector2f(cell->getPosition() * 0.98f), cell->getSize()));
                        numberCells++;
                        break;
                    }
                }
                break;
            }
            // we don't process other types of events
            default:
                break;
    }

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

           /* Update the scene */
            for (auto cell : *cells) {
                cell->update(dt);
            } 

            // Draw our game scene here

            for (auto cell : *cells) {
                window.draw(*cell->draw());
            } 
                
            // Show everything we just drew
            window.display();
       }
    }

    for (auto cell : *cells) {
        delete cell;
    } 
    delete cells;

    return 0;
}

