#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Snake {
    public:
        Snake(int width, int height, int pos);
        void update(sf::Time dt);
        std::vector<sf::Shape*> draw();
    private:
       
};