#pragma once
#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Shooteable.hpp"
#include <random>
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>

class Bullet : public sf::Drawable, protected sf::Transformable,  public Shooteable{
    public:
        Bullet(int width, int height);
        void update(sf::Time dt, std::vector<Shooteable*> &objetives);
        void update(sf::Time dt, Shooteable* player);
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void shoot(float oriX, float oriY, int direction);
        sf::Rect<float> getHitbox();
        void kill ();
        bool getIsRunning();
    private:
        int turn = 0;
        int screenHeight, screenWidth;
        float speed;
        bool isRunning;
        sf::Rect<float> hitbox;
        sf::Vector2i size;
        sf::Vector2f position;
        sf::Texture bulletTexture;
        sf::VertexArray bulletVertexs;
        sf::SoundBuffer shootSoundBuffer, explosionBuffer;
        sf::Sound shootSound, explosionSound;
};