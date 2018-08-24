#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Spark {
    public:
        Spark();
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        void restart(int x, int y, sf::Color color, int n);
        static const int maxSparks = 100;
        ~Spark();
    private:
        sf::Vector2f *position;
        sf::RectangleShape *body;
        sf::Vector2f *speed;
};