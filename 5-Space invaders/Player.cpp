#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Player {
    public:
        Player(int width, int height);
        void update(sf::Time dt);
        sf::RectangleShape draw ();
    private:
        void init();
};