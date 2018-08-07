#include "Alien.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime> // To seed the generator.
#include <unistd.h>
#include <chrono>
#include <vector>

Alien::Alien(int width, int height, int row, int col) {
    screenWidth = width;
    screenHeight = height;

    size = sf::Vector2i (width/13, height/10);
    drawing = new sf::VertexArray();

    _row = row;
    _col = col;
}

bool Alien::loadTexture (sf::Texture &styleSheet) {

    alienTexture = styleSheet;
    alienVertexs.setPrimitiveType(sf::Quads);
    alienVertexs.resize(8);
    drawing->setPrimitiveType(sf::Quads);
    drawing->resize(4);

    //First state
    alienVertexs[0].position = sf::Vector2f(0, 0);
    alienVertexs[1].position = sf::Vector2f(30, 0);
    alienVertexs[2].position = sf::Vector2f(30, 21);
    alienVertexs[3].position = sf::Vector2f(0, 21);

    // define its 4 texture coordinates
    alienVertexs[0].texCoords = sf::Vector2f(0, 0);
    alienVertexs[1].texCoords = sf::Vector2f(30, 0);
    alienVertexs[2].texCoords = sf::Vector2f(30, 21);
    alienVertexs[3].texCoords = sf::Vector2f(0, 21);


    //Second state
    alienVertexs[4].position = sf::Vector2f(0, 0);
    alienVertexs[5].position = sf::Vector2f(30, 0);
    alienVertexs[6].position = sf::Vector2f(30, 21);
    alienVertexs[7].position = sf::Vector2f(0, 21);

    // define its 4 texture coordinates
    alienVertexs[4].texCoords = sf::Vector2f(0, 24);
    alienVertexs[5].texCoords = sf::Vector2f(30, 24); 
    alienVertexs[6].texCoords = sf::Vector2f(30, 45);
    alienVertexs[7].texCoords = sf::Vector2f(0, 45);

    setPosition(sf::Vector2f(_col * size.x + size.x, _row * size.y + size.y ));
    setScale(3, 3);
}

void Alien::update () {
}

void Alien::changeState(bool isDead) {
    if (!isDead) {
        state = (state == one) ? two : one;
    }
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // apply the texture
        states.texture = &alienTexture;

        // you may also override states.shader or states.blendMode if you want

        int inicio = state * 4;
        int j = 0;
        for (int i = inicio; i < inicio + 4; i++){
            drawing[0][j] = alienVertexs[i];
            j++;
        }

        // draw the vertex array
        target.draw(*drawing, states);
    
}

