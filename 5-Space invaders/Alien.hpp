#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Alien {
    public:
        Alien(int width, int height, int pos);
        void update(sf::Time dt);
        sf::RectangleShape draw ();
    private:
        void init();
};