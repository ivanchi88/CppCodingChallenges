#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Drop {
    public:
        Drop(int width, int height, int pos);
        void update(sf::Time dt);
        sf::RectangleShape draw ();
    private:
        void init();

        sf::RectangleShape* body;
        float speed;
        sf::Vector2<float> size;
        int screenWidth, screenHeight;

        float minSpeed = 600, maxSpeed = 1000;
        float minification = 0.001;

        std::mt19937_64 gen;
        std::uniform_real_distribution<double> randSpeed;
        std::uniform_int_distribution<int> randPos;

        int p;
};