#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>


class Cell {
    public:
        Cell();
        Cell(int width, int height, int row, int col, int size);
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        sf::Vector2i getPosition();
        sf::RectangleShape* getBackground();

        sf::Vector2f getAB();
        sf::Vector2f getLastAB();
        void setAB(float a, float b);
        void setLastAB(sf::Vector2f ab);
        ~Cell();
    private:
        int screenWidth, screenHeight, row, col; 
        float A, B, Aant, Bant;
        sf::RectangleShape *background;
        float size;
};