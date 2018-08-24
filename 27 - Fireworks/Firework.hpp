#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include "Spark.hpp"
#include <SFML/Audio.hpp>

#include <unistd.h>

class Firework {
    public:
        Firework(int width, int height);
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        void restart();
        void setBuffers(sf::SoundBuffer &launchBuffer, sf::SoundBuffer &explosionBuffer);
        ~Firework();
    private:
        int screenWidth, screenHeight, size;
        int bodyParts;
        float speed;
        bool isFirstExplosion;
        bool hasBeenLaunched;
        sf::Vector2f *position;
        std::vector<Spark*> *sparks;
        std::vector<sf::RectangleShape*> *body;
        sf::Color *color;
        sf::Sound launchSound, explosionSound;
};