#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>


class Planet {
    public:
        Planet(int width, int height);
        Planet(int width, int height, sf::Vector2f *position, float radius);
        void update(sf::Time dt);
        sf::CircleShape* draw();
        ~Planet();
    private:
};