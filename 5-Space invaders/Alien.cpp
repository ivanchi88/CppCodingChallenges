#include "Alien.hpp"

Alien::Alien(int width, int height, int row, int col) {
    screenWidth = width;
    screenHeight = height;

    size = sf::Vector2i (width/22, height/20);
    drawing = new sf::VertexArray();

    _row = row;
    _col = col;

    explosionBuffer.loadFromFile("resources\\sounds\\alienExplosion.wav");
    explosionSound.setBuffer(explosionBuffer);
}

bool Alien::loadTexture (sf::Texture &styleSheet) {

    alienTexture = styleSheet;
    alienVertexs.setPrimitiveType(sf::Quads);
    alienVertexs.resize(12); /* First state, second and diying */
    drawing->setPrimitiveType(sf::Quads);
    drawing->resize(4);

    //First state
    alienVertexs[0].position = sf::Vector2f(0, 0);
    alienVertexs[1].position = sf::Vector2f(1, 0);
    alienVertexs[2].position = sf::Vector2f(1, 1);
    alienVertexs[3].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    alienVertexs[0].texCoords = sf::Vector2f(0, 0);
    alienVertexs[1].texCoords = sf::Vector2f(30, 0);
    alienVertexs[2].texCoords = sf::Vector2f(30, 22);
    alienVertexs[3].texCoords = sf::Vector2f(0, 22);


    //Second state
    alienVertexs[4].position = sf::Vector2f(0, 0);
    alienVertexs[5].position = sf::Vector2f(1, 0);
    alienVertexs[6].position = sf::Vector2f(1, 1);
    alienVertexs[7].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    alienVertexs[4].texCoords = sf::Vector2f(0, 24);
    alienVertexs[5].texCoords = sf::Vector2f(30, 24); 
    alienVertexs[6].texCoords = sf::Vector2f(30, 46);
    alienVertexs[7].texCoords = sf::Vector2f(0, 46);

    //Dying state
    alienVertexs[8].position = sf::Vector2f(0, 0);
    alienVertexs[9].position = sf::Vector2f(1, 0);
    alienVertexs[10].position = sf::Vector2f(1, 1);
    alienVertexs[11].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    alienVertexs[8].texCoords = sf::Vector2f(107, 0);
    alienVertexs[9].texCoords = sf::Vector2f(148, 0); 
    alienVertexs[10].texCoords = sf::Vector2f(148, 19);
    alienVertexs[11].texCoords = sf::Vector2f(107, 19);

    
    setScale(size.x , size.y);

    hitbox.width = size.x;
    hitbox.height = size.y;

    position.x = _col * (size.x + size.x * 0.5) + size.x;
    position.y = _row * (size.y + size.y * 0.3) + size.y;

    setPosition(position);

    hitbox.left = position.x;
    hitbox.top = position.y;
    return true;
}

void Alien::update (sf::Vector2f speed) {
    if (state != State::dead && state != State::dying) {
            this->changeState(false);
            position += speed;
            hitbox.left = position.x;
            hitbox.top = position.y;
            this->setPosition(position);
    } else {
        state = State::dead;
    }
}

void Alien::changeState(bool isDead) {
    if (!isDead) {
        state = (state == State::one) ? State::two : State::one;
    } else {
        state = State::dying;
    }
}

sf::Rect<float> Alien::getHitbox(){
    return this->hitbox;
}

State Alien::getState() {
    return this->state;
}

sf::Vector2f Alien::getPosition () {
    return position;
}

sf::Vector2i Alien::getSize() {
    return size;
}

void Alien::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

        // apply the texture
        states.texture = &alienTexture;

        // you may also override states.shader or states.blendMode if you want

        if (state != State::dead) {

            int inicio = (int) state * 4;
            int j = 0;
            for (int i = inicio; i < inicio + 4; i++){
                drawing[0][j] = alienVertexs[i];
                j++;
            }


            sf::RectangleShape r;
            r.setFillColor(sf::Color(255, 20, 50));
            r.setOutlineColor(sf::Color(100, 200, 100));
            r.setOutlineThickness(1);
            r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
            r.setPosition(hitbox.left, hitbox.top);
            //std::cout << size.x << " " << size.y << std::endl;
            //target.draw(r);    

            // draw the vertex array
            target.draw(*drawing, states);
        }
}

void Alien::kill(){
    std::cout << "killed "  << _col << " " << _row << std::endl;
    changeState(true);
    hitbox.top = -size.y * 2;
    hitbox.left = -size.x *2;
    explosionSound.play();
}

bool Alien::getIsRunning() {
    return state == State::one || state == State::two;
}

