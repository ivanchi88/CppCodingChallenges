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


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "SFML OpenGL");
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock Clock;


    glClearDepth(1.f);
    glClearColor(0.3f, 0.3f, 0.3f, 0.f);
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    //// Setup a perspective projection & Camera position
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar

    bool rotate=true;
	float angle;

    while (window.isOpen())
    {
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
				rotate=!rotate;
			}
 
		}
        
        //Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Apply some transformations for the cube
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -200.f);
		
		if(rotate){
			angle=Clock.getElapsedTime().asSeconds();
		}
		glRotatef(angle * 50, 1.f, 0.f, 0.f);
		glRotatef(angle * 30, 0.f, 1.f, 0.f);
		glRotatef(angle * 90, 0.f, 0.f, 1.f);
			
		
		 
		//Draw a cube
       glBegin(GL_QUADS);//draw some squares
            glColor3f(0,1,1); //cyan
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f( 50.f,  50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);

            glColor3f(0,0,1); //blue
            glVertex3f( 50.f, -50.f, 50.f);
            glVertex3f( 50.f,  50.f, 50.f);
            glVertex3f(-50.f,  50.f, 50.f);
            glVertex3f(-50.f, -50.f, 50.f);

            glColor3f(1,0,1); //magenta
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f,  50.f,  50.f);
            glVertex3f(-50.f,  50.f, -50.f);
            glVertex3f(-50.f, -50.f, -50.f);

            glColor3f(0,1,0); //green
            glVertex3f(50.f, -50.f, -50.f);
            glVertex3f(50.f,  50.f, -50.f);
            glVertex3f(50.f,  50.f,  50.f);
            glVertex3f(50.f, -50.f,  50.f);

            glColor3f(1,1,0); //yellow
            glVertex3f(-50.f, -50.f,  50.f);
            glVertex3f(-50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f, -50.f);
            glVertex3f( 50.f, -50.f,  50.f);

            glColor3f(1,0,0); //red
            glVertex3f( 50.f, 50.f,  50.f);
            glVertex3f( 50.f, 50.f, -50.f);
            glVertex3f(-50.f, 50.f, -50.f);
            glVertex3f(-50.f, 50.f,  50.f);

        glEnd();
            // Show everything we just drew
            window.display();
       }
    
}
