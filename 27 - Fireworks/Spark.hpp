#include <iostream>
#include <SFML/Graphics.hpp>

class Spark {
    public:
        Spark(int width, int height, int row, int col, int size);
        void update(sf::Time dt);
        void draw(sf::RenderWindow& target);
        void setVisited();
        bool getIsVisited();
        void breakWall(int index); /* 0 = top 1 = right 2 = bottom 3 = left */
        sf::Vector2i getPosition();
        sf::RectangleShape* getBackground();
        ~Spark();
    private:
        sf::Vector2f *position;
        sf::Vector2f * size;
};