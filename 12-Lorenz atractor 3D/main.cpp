#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <chrono> //For system_clock
#include <unistd.h>
#include "GL/glu.h"

#define assetsFolder "./resources/" 

struct Point {
    float x, y, z;
};

int main(int agrc, char *argv[])
{

    float w = 800.0, h = 600.0;
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 0;
    settings.antialiasingLevel = 4;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    sf::Window window(sf::VideoMode(w, h, 32), "SFML OpenGL", sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    /* Game variables*/
    sf::Clock clock;

    /* Activate depth test */
    glEnable(GL_DEPTH_TEST);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, w/h, 1.0f, 200.0f);

    std::vector<Point*> *points = new std::vector<Point*>();
    points->push_back(new Point {(rand() % 100) * 0.001, (rand() % 100) * 0.001, (rand() % 100) * 0.001});

    Point *lastPoint = (*points)[0];

    float distance = 0;
    float rotationSpeed = 1.0;

    float dx = 0;
    float dy = 0;
    float dz = 0;

    float a = 10.0, c = 10.0/3.0, b = 28;

    float rotation = 0.0;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        // Process events
        sf::Event Event;
        while (window.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                window.close();

            // Escape key : exit
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
                window.close();

            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::W))
                distance += 1;

            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::S))
                distance -= 1;
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A))
                rotationSpeed -= 2.0;
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::D))
                rotationSpeed += 2.0;
            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space)){
                distance = 0;
                rotationSpeed = 0;
            }
                
 
		}
        
        //Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, distance -20.f);

        /* add a new vertex */
        float dx = (a * (lastPoint->y - lastPoint->x)) * dt.asSeconds()  ;
        float dy = (lastPoint->x * (b - lastPoint->z) - lastPoint->y) * dt.asSeconds() ;
        float dz = (lastPoint->x * lastPoint->y - c * lastPoint->z) * dt.asSeconds();

        points->push_back(new Point {lastPoint->x + dx, lastPoint->y + dy, lastPoint->z + dz});
        lastPoint = (*points)[points->size() -1];
        /* draw */

        int i = 0;

        glRotatef(rotation, 0.0f, 1.0f, 0.0f);
        rotation+= dt.asSeconds() * 5.0 * rotationSpeed;
        glScalef(0.05f, 0.05f, 0.05f);

        glPointSize(2.0f);
        glBegin(GL_POINTS);
        
        for (auto point : *points) {

            glColor3f(0.5, 0.2, 0.9);
            glVertex3f(point->x, point->y, point->z);
            //std::cout << point->x << " " << point->y << " " <<  point->z << std::endl;
        }

        glEnd( );

			
        // Show everything we just drew
        window.display();
       }
    
}
