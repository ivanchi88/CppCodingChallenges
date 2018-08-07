#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Alien : public sf::Drawable, protected sf::Transformable{
    public:
        Alien(int width, int height, int row, int col);
        void update();
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void changeState (bool isDead);
        enum State { one, two, dead };
    private:
        void init();
        int screenHeight, screenWidth, _row, _col;
        sf::Vector2i size;
        sf::Texture alienTexture;
        sf::VertexArray alienVertexs;
        sf::VertexArray *drawing;
        State state = one;
};