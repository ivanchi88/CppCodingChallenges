#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Snake {
    public:
        Snake(int width, int height, int cellSiz, int snakeSiz);
        void update(sf::Vector2<int> *prize);
        std::vector<sf::RectangleShape*> draw ();
        void move(int x, int y);
    private:
        void moveBody();
        void init();
        bool checkCollitions(sf::Vector2<int> newHead);
        std::vector<sf::Vector2<int>> body;
        sf::Vector2<int> speed;
        int cellSize, snakeSize, originalSnakeSize, cellNumber;
        int screenWidth, screenHeight;
};