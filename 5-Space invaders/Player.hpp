#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include "Bullet.hpp"
#include "State.hpp"
class Player : public sf::Drawable, protected sf::Transformable {
    public:
        Player(int width, int height);
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void move(float direction);
        void update(sf::Time dt);
        void shoot();
        sf::Rect<float> getHitbox();
    private:
        int screenHeight, screenWidth;
        float speed, minSpeed;
        sf::Rect<float> hitbox;
        sf::Vector2f size;
        sf::Vector2f position;
        sf::Texture shipTexture;
        sf::VertexArray shipVertexs;
        sf::VertexArray *drawing;
        State state;
        Bullet* bullet;
};