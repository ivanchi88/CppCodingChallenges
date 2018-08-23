#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 800, height = 800;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;

    int cellSize = 15;
    Snake snake(width, height, cellSize , 10);

    sf::Vector2<int> prize;

    srand(time(0));

    prize.x = rand() % (width/cellSize) -1;
    prize.y = rand() % (width/cellSize) -1;

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            snake.move(-1, 0);
        }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            snake.move(1, 0);
        }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            snake.move(0, -1);
        }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            snake.move(0, 1);
        }

        /*     
        ****************************************     
        Update the scene :)
        ****************************************     
        */

       if (!isPaused) {

           snake.update(&prize);
            // Draw our game scene here
            sf::RectangleShape prizR;
            prizR.setPosition(prize.x * cellSize, prize.y * cellSize);
            prizR.setSize(sf::Vector2f(cellSize, cellSize));
            prizR.setFillColor(sf::Color(200, 10, 100));
            window.draw(prizR);

            for (auto cellR : snake.draw()) {
                window.draw(*cellR);
                delete cellR;
            }
            // Show everything we just drew
            window.display();
            usleep(100000);
       }
    }

    return 0;
}
