#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>
#include "Spark.hpp"


class Firework {
    public:
        Firework(int width, int height);
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        void restart();
        ~Firework();
    private:
        int screenWidth, screenHeight, size;
        int bodyParts;
        float speed;
        sf::Vector2f *position;
        std::vector<Spark*> *sparks;
        std::vector<sf::RectangleShape*> *body;
        sf::Color *color;
};