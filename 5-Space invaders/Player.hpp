#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include "Bullet.hpp"
#include "State.hpp"
#include "Shooteable.hpp"
#include <SFML/Audio.hpp>

class Player : public sf::Drawable, protected sf::Transformable, public Shooteable{
    public:
        Player(int width, int height);
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void move(float direction);
        void update(sf::Time dt, std::vector<Shooteable*> objetives);
        void shoot();
        sf::Rect<float> getHitbox();
        Bullet* getBullet();
        void kill ();
        bool getIsRunning();
    private:
        int screenHeight, screenWidth;
        float speed, minSpeed;
        sf::Rect<float> hitbox;
        sf::Vector2f size;
        sf::Vector2f position;
        sf::Texture shipTexture;
        sf::VertexArray shipVertexs;
        sf::VertexArray *drawing;
        State state;
        Bullet* bullet;
        sf::SoundBuffer  gameOverSoundBuffer;
        sf::Sound gameOverSound;
};