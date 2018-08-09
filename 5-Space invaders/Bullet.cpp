#include "Bullet.hpp"

Bullet::Bullet(){

}

Bullet::Bullet(int width, int height){
    screenWidth = width;
    screenHeight = height;
}

bool Bullet::loadTexture (sf::Texture &styleSheet) {

    bulletTexture = styleSheet;
    bulletVertexs.setPrimitiveType(sf::Quads);
    bulletVertexs.resize(12); /* First state, second and diying */
    drawing->setPrimitiveType(sf::Quads);
    drawing->resize(4);

    //First state
    bulletVertexs[0].position = sf::Vector2f(0, 0);
    bulletVertexs[1].position = sf::Vector2f(1, 0);
    bulletVertexs[2].position = sf::Vector2f(1, 1);
    bulletVertexs[3].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    bulletVertexs[0].texCoords = sf::Vector2f(0, 0);
    bulletVertexs[1].texCoords = sf::Vector2f(30, 0);
    bulletVertexs[2].texCoords = sf::Vector2f(30, 22);
    bulletVertexs[3].texCoords = sf::Vector2f(0, 22);

    setScale(size.x , size.y);

    //size.x = getScale().x;
    //size.y = getScale().y;

    position.x = _col * (size.x + size.x * 0.3) + size.x;
    position.y = _row * (size.y + size.y * 0.3) + size.y;
    return true;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // apply the texture
        states.texture = &bulletTexture;

        // you may also override states.shader or states.blendMode if you want

        int inicio = (int) state * 4;
        int j = 0;
        for (int i = inicio; i < inicio + 4; i++){
            drawing[0][j] = bulletVertexs[i];
            j++;
        }

        bool hitBox = true;

        if (hitBox) {
            sf::RectangleShape r;
            r.setFillColor(sf::Color(255, 20, 50));
            r.setOutlineColor(sf::Color(100, 200, 100));
            r.setOutlineThickness(1);
            r.setSize(sf::Vector2f(size.x, size.y));
            r.setPosition(position);
            //std::cout << size.x << " " << size.y << std::endl;
            target.draw(r);    
        }

        // draw the vertex array
        target.draw(*drawing, states);
}