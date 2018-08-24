#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>


class Blob {
    public:
        Blob(int width, int height);
        void update(sf::Time dt);
        float getRadius();
        sf::Vector2f getPosition();
        ~Blob();
    private:
        int screenWidth, screenHeight, radius;
        sf::Vector2f *speed;
        sf::Vector2f *position;
};