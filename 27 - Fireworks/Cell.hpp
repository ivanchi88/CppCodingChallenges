#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <math.h>


class Cell {
    public:
        Cell(int width, int height, int row, int col, int size);
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        void setVisited();
        bool getIsVisited();
        void breakWall(int index); /* 0 = top 1 = right 2 = bottom 3 = left */
        sf::Vector2i getPosition();
        sf::RectangleShape* getBackground();
        ~Cell();
    private:
        int screenWidth, screenHeight, row, col; 
        sf::VertexArray *walls;
        sf::RectangleShape *background;
        bool wall [4] {true, true, true, true}; /* top right bottom left */
        float size;
        bool isVisited;
};