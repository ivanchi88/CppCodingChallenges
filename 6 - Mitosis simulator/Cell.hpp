#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <random>
#include <chrono>
#include <unistd.h>

class Cell {
    public:
        Cell(int width, int height);
        Cell(int width, int height, sf::Vector2f *position, float radius);
        void update(sf::Time dt);
        bool containsPoint(sf::Vector2f *point);
        sf::Vector2f getPosition();
        float getSize();
        sf::CircleShape* draw();
        ~Cell();
    private:
        std::mt19937_64 *gen = nullptr;
        std::uniform_real_distribution<float> *randSpeed = nullptr, *randPosition = nullptr;
        sf::Vector2f *speed = nullptr;
        sf::CircleShape *body;
        int screenWidth, screenHeight;
        float maxSpeed = 80;
};