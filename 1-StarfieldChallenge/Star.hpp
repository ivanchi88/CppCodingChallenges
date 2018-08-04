#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Star {
    public:
        Star(int width, int height, int pos);
        void update(sf::Time dt);
        std::vector<sf::Shape*> draw();
    private:
        double module();
        void changeSize();
        void init();
        bool isOutOfBorders();
        int calculateTrailAngle();
        float xSpeed, ySpeed, windowWidth, windowHeight;
        float size;
        sf::CircleShape* circle;
        const float minSize = 0.5;
        const float reductionFactor = 0.0015;
        const float maxSpeed = 350.0;
        const float minSpeed = 0.0;
        const float accelFactor = 0.015;

        int trailAngle = 0;
        const float trailLength = 20;
        std::vector<sf::Shape*> drawings;

        std::mt19937_64 gen;
        std::uniform_real_distribution<double> randSpeed;
        std::uniform_int_distribution<int> randPos;
        std::uniform_int_distribution<int> ballDirection;
};