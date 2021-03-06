#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Alien.hpp"
#include "Player.hpp"
#include <chrono> //For system_clock
#include <unistd.h>
#include "State.hpp"
#include <SFML/Audio.hpp>

#define assetsFolder "./resources/" 


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    //settings.antialiasingLevel = 8;

    int width = 1920, height =1080 ;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Fullscreen, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    /* Game variables*/
    sf::Clock clock;
    sf::Clock turnClock;


    sf::Texture spriteSheet;
    spriteSheet.loadFromFile("resources\\graphics\\spaceInvaders.png");

    sf::SoundBuffer  alienMoveBuffer;
    alienMoveBuffer.loadFromFile("resources\\sounds\\alienMove2.wav");
    sf::Sound alienMove;
    alienMove.setBuffer(alienMoveBuffer);

    sf::SoundBuffer  changeRowBuffer;
    changeRowBuffer.loadFromFile("resources\\sounds\\changeRow1.wav");
    sf::Sound changeRow;
    changeRow.setBuffer(changeRowBuffer);


    int aliensWidth = 11;
    int aliensHeight = 5;
    std::vector<Alien*> aliens;
    std::vector<Bullet*> enemyBullets;
    std::vector<Shooteable*> thingsToShoot;
    int maxBullets = 5;
    int i;

    for (i = 0; i < maxBullets; i++) {
        enemyBullets.push_back(new Bullet(width, height));
        thingsToShoot.push_back(enemyBullets[i]);
        enemyBullets[i]->loadTexture(spriteSheet);
    }

    i = 0;
    for (int row = 0; row < aliensHeight; row++) {
        for (int column = 0; column < aliensWidth; column++){
            aliens.push_back(new Alien(width, height, row, column));
            thingsToShoot.push_back(aliens[i]);
            aliens[i]->loadTexture(spriteSheet);
            i++;
        }
    }


    srand(time(NULL));

    Player player(width, height);
    player.loadTexture(spriteSheet);

    bool isPaused = false;

    int row, col;
    turnClock.restart();
    sf::Vector2f speed(10, 0);
    int delay = 750;
    bool isShooting = false;
    sf::Vector2f bulletOrigin;
    bool gameOver = false;
    int alive = 1;
    while (window.isOpen())
    {
        if (gameOver) {
            usleep(1000000);
            break;
        }
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

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::A)){
				player.move(-1.0);
			} else 
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::D)){
				player.move(1.0);
			} else 
            if ((event.type == sf::Event::KeyReleased) && ((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::D))){
				player.move(0.0);
			} else
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::W)){
				player.shoot();
			} else
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space)){
				player.shoot();
			}
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
            /* Change aliens of row */
            for (row = 0; row < aliensHeight; row++) {
                for (col = 0; col < aliensWidth; col++){
                    if (aliens[i]->getState() != State::dead){
                        if ((aliens[i]->getPosition().x + speed.x < 10) || (aliens[i]->getPosition().x + speed.x > width - aliens[i]->getSize().x)) {
                            speed.x = -speed.x;
                            delay *= 0.6;
                            speed.y = aliens[i]->getSize().y - 2 / 3;
                        }
                    }
                    i++;
                }
            }
            if (speed.y != 0) {
                changeRow.play();
            }
            
            alive = 0;
            /* Move aliens */
            i = 0;
            for (row = 0; row < aliensHeight; row++) {
                for (col = 0; col < aliensWidth; col++){
                    if (aliens[i]->getState() != State::dead) {
                        aliens[i]->update(speed);
                        if ((!isShooting) && rand() % 1000< 5) {
                            bulletOrigin.x = aliens[i]->getPosition().x + aliens[i]->getSize().x/2;
                            bulletOrigin.y = aliens[i]->getPosition().y + aliens[i]->getSize().y;
                            isShooting = true;
                        }
                        if ( (aliens[i]->getIsRunning() && aliens[i]->getHitbox().intersects(player.getHitbox())) || aliens[i]->getPosition().y >= player.getPosition().y) {
                            player.kill();
                        }
                        alive++;
                    }
                    //std::cout << aliensToShoot[i]->getHitbox().left << " " << aliens[i]->getHitbox().left << std::endl;
                    i++;
                }
            }
            speed.y = 0;
            turnClock.restart();
            alienMove.play();
        }
        

        for (auto bullet : enemyBullets) {
            if ((!bullet->getIsRunning() && isShooting))  {
                bullet->shoot(bulletOrigin.x, bulletOrigin.y, 1);
                isShooting = false;
                break;
            }
            bullet->update(dt, &player);
        }

        player.update(dt, thingsToShoot);

        gameOver = (!player.getIsRunning()) || (alive == 0);

        // Show everything we just drew

        i = 0;
        for (row = 0; row < aliensHeight; row++) {
            for (col = 0; col < aliensWidth; col++){
                window.draw(*aliens[i]);
                i++;
            }
        }

        for (auto bullet : enemyBullets) {
            window.draw(*bullet);
        }
        window.draw(*player.getBullet());
        window.draw(player);

        window.display();
       }
    }

    return 0;
}
