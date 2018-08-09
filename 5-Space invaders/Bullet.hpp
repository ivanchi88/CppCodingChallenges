#include <SFML/Graphics.hpp>
#include"State.hpp"
#include <random>
#include <vector>

class Bullet : public sf::Drawable, protected sf::Transformable{
    public:
        Bullet(int width, int height);
        Bullet();
        void update(sf::Vector2f speed);
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    private:

        int screenHeight, screenWidth, _row, _col;
        sf::Rect<float> hitbox;
        sf::Vector2i size;
        sf::Vector2f position;
        sf::Texture bulletTexture;
        sf::VertexArray bulletVertexs;
        sf::VertexArray *drawing;
        State state = State::one;
};