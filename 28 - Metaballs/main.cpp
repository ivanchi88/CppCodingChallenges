#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Blob.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 


int t = 0;

float dist (int x, int y, int a,int  b);

int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 500, height = 500;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    const int blobNumber = 4;
    std::vector<Blob*> *blobs = new std::vector<Blob*>;

    for (int i = 0; i < blobNumber; i++){
        blobs->push_back(new Blob(width, height));
    }

    sf::Image image;
    image.create(width, height, sf::Color(0, 0, 0));

    sf::Sprite sprite;
    sf::Texture painting;

    /* Game variables*/
    sf::Clock clock;

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
        /*     
        ****************************************     
        Update the scene :)
        ****************************************     
        */

       if (!isPaused) {  
           /* Update the scene */
            for (auto b : *blobs){
                b->update(dt);
            }
           /* draw */
           float sum;
            for(int y = 0; y < height; y++)
            {
                for(int x = 0; x < width; x++)
                {   
                    sum = 0;
                    for (auto b : *blobs) {
                        sum +=  (50.0 * b->getRadius() )/ dist(x, y, b->getPosition().x, b->getPosition().y);
                    }
                    image.setPixel(x, y, {(sum > 255) ? 255: sum, (sum > 255) ? 150: sum * 0.2, (sum > 255) ? 220: sum});
                }
            }
            painting.loadFromImage(image);
            sprite.setTexture(painting);
            window.draw(sprite);
            window.display();
       }
    }
    return 0;
}

float dist (int x, int y, int a,int  b) {
    float d1 = x - a;
    d1 *= d1;
    float d2 = y - b;
    d2 *= d2;
    d1 += d2;
    return sqrt(d1);
}

