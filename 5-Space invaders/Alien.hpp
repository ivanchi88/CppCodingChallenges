#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>
#include <iostream>
#include "State.hpp"
#include "Shooteable.hpp"

class Alien : public sf::Drawable, protected sf::Transformable,  public Shooteable{
    public:
        Alien(int width, int height, int row, int col);
        void update(sf::Vector2f speed);
        bool loadTexture(sf::Texture &styleSheet);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        void changeState (bool isDead);
        sf::Vector2f getPosition ();
        sf::Vector2i getSize();
        State getState ();
        sf::Rect<float> getHitbox();
        void kill();
    private:
        void init();
        int screenHeight, screenWidth, _row, _col;
        sf::Rect<float> hitbox;
        sf::Vector2i size;
        sf::Vector2f position;
        sf::Texture alienTexture;
        sf::VertexArray alienVertexs;
        sf::VertexArray *drawing;
        State state = State::one;
};