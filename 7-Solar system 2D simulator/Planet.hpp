#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>


class Planet {
    public:
        Planet(int width, int height);
        Planet(int width, int height, sf::Vector2f *position, float radius, int level, float distanceToParent_);
        void update(sf::Time dt, sf::Vector2f const &parentPos);
        float getRadius();
        void draw(sf::RenderWindow& target);
        ~Planet();
    private:
        int screenWidth, screenHeight;
        sf::CircleShape* body;
        std::vector<Planet*> *asteroids;
        sf::Vector2f *parentPos;
        float distanceToParent;
        float angle;
        void rotate ();
        float speed;
};