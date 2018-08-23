#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono> //For system_clock
#include <unistd.h>
#include <math.h> 
#define assetsFolder "./resources/" 

const int maxLevel = 7;
int t = 0;

void divideTree(sf::Vector2f bottom, sf::Vector2f top, sf::Vertex line[], int level, int direction, sf::RenderWindow &window);

int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1920, height = 1080;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Fullscreen, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;

    int maxDrops = 800;

    window.clear(sf::Color(15, 15, 15));
    
    std::random_device rd;
    sf::Vector2f bottom, top;
    bottom.x = width/2;
    bottom.y = height;

    top.x = bottom.x;
    top.y = height - height/4;

    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(bottom.x, bottom.y)),
        sf::Vertex(sf::Vector2f(top.x, top.y))
    };

    divideTree(bottom, top, line, 0, 0, window);

    bool isPaused = false;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        //window.clear(sf::Color(15, 15, 15));

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

        // Show everything we just drew
        //
        window.display();
       }
    }

    return 0;
}

void divideTree(sf::Vector2f bottom, sf::Vector2f top, sf::Vertex line[], int level, int direction, sf::RenderWindow &window){
    line[0].position = bottom;
    line[1].position = top;
    std::cout << t << std::endl;
    t++;
    
        
    window.draw(line, 2, sf::Lines);
    if (level == maxLevel) {
    sf::CircleShape c;
    int r = 10;
    c.setFillColor({150, 20, 150, 220});
    c.setRadius(r);
    c.setPosition(top.x - r , top.y - r);
    window.draw(c);
    }

    
    if (level < maxLevel) {
        float x;
        float distA = bottom.x - top.x;
        distA *= distA;
        float distB = bottom.y - top.y;
        distB *= distB;

        distA = distA + distB;
        distA = sqrt(distA);
        distB = abs(bottom.x - top.x);

        bottom = top;

        float aperture = 1.0;
        /* rama izquierda */
        top.y = bottom.y - ((level % 2) != 0 ? (direction == -1 ? 0.5 : 1) : 1) * distA/2;
        top.x = bottom.x + ((level % 2) != 0 ? (direction == 1 ? 0 : -1) : -1) * ((distA/2 + (level ))/ aperture);
        std::cout << bottom.x <<  " A " << level <<  " direccion " << distA << std::endl;
        divideTree(bottom, top, line, level + 1, (-1) ,window);
        /* rama derecha */
        //std::cout << bottom.x <<  " B " << level << " direccion " << direction << std::endl;
        top.y = bottom.y - ((level % 2) != 0 ? (direction == 1 ? 0.5 : 1) : 1) * distA/2;
        top.x = bottom.x + ((level % 2) != 0 ? (direction == -1 ? 0 : 1) : 1) * ((distA/2 + (level))/ aperture);
        divideTree(bottom, top, line, level + 1, (1), window);
    }
}