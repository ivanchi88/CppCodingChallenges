#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include "Box.hpp"
#include <chrono> //For system_clock
#include <unistd.h>
#include "GL/glu.h"

#define assetsFolder "./resources/" 

void divideAll (std::vector<Box> *boxes);


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

    /* Game variables*/
    sf::Clock Clock;
    sf::Clock clock;

    //prepare OpenGL surface for HSR
	//glClearDepth(1.f);
    //glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    //glDepthMask(GL_TRUE);
    //glDepthFunc(GL_EQUAL);
   // glCullFace(GL_BACK);
   // glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(60.0f, w/h, 1.0f, 100.0f);
    

    bool rotate=true;
	float angle = 0;

    Box b(0, 0, 0, 2);
    std::vector<Box> *boxes = new std::vector<Box>();
    boxes->push_back(b);
    float lastTime = Clock.getElapsedTime().asSeconds();

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

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::A)){
				angle+=0.5;
			}

            if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Space)){
                if (Clock.getElapsedTime().asSeconds() - lastTime > 3 ) {
				    divideAll(boxes);
                    lastTime = Clock.getElapsedTime().asSeconds();
                }
			}
 
		}
        
        //Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -5.f);
		
        /* Keeps rotating */
		if(rotate){
			angle=Clock.getElapsedTime().asSeconds();
		}
		glRotatef(angle * 50, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 90, 0.f, 0.f, 1.f);

        /* draw */

        int i = 0;
        for (Box box : *boxes) {
            box.draw();
        }
			
        // Show everything we just drew
        window.display();
       }
    
}

void divideAll (std::vector<Box> *boxes) {
    std::vector<Box> *vectors = new std::vector<Box>();
    int i = 0;
    for (auto box : *boxes) {
        for (auto b : box.divide()) {
            vectors->push_back(b);
        }
    }
    *boxes = *vectors;
}
