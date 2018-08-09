#include "Player.hpp"

Player::Player(int width, int height) {
    screenWidth = width;
    screenHeight = height;

    size = sf::Vector2f (width/15, height/12);
    drawing = new sf::VertexArray();
    state = State::one;
    minSpeed = 500;
    speed = 0;
    bullet = new Bullet(width, height);
}

void Player::move(float direction) {
    speed = direction * minSpeed;
}

void Player::shoot () {

}

sf::Rect<float> Player::getHitbox(){

}

bool Player::loadTexture (sf::Texture &styleSheet) {

    shipTexture = styleSheet;
    shipVertexs.setPrimitiveType(sf::Quads);
    shipVertexs.resize(8); /* First state, and diying */
    drawing->setPrimitiveType(sf::Quads);
    drawing->resize(4);


    //First state
    shipVertexs[0].position = sf::Vector2f(0, 0);
    shipVertexs[1].position = sf::Vector2f(1, 0);
    shipVertexs[2].position = sf::Vector2f(1, 1);
    shipVertexs[3].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    shipVertexs[0].texCoords = sf::Vector2f(68, 23);
    shipVertexs[1].texCoords = sf::Vector2f(98, 23);
    shipVertexs[2].texCoords = sf::Vector2f(98, 45);
    shipVertexs[3].texCoords = sf::Vector2f(68, 45);

    //Dying state
    shipVertexs[4].position = sf::Vector2f(0, 0);
    shipVertexs[5].position = sf::Vector2f(1, 0);
    shipVertexs[6].position = sf::Vector2f(1, 1);
    shipVertexs[7].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    shipVertexs[4].texCoords = sf::Vector2f(107, 0);
    shipVertexs[5].texCoords = sf::Vector2f(148, 0); 
    shipVertexs[6].texCoords = sf::Vector2f(148, 19);
    shipVertexs[7].texCoords = sf::Vector2f(107, 19);


    setScale(size);
    
    position.x = screenWidth / 2 - size.x/2;
    position.y = screenHeight - size.y * 1.5 ;

    setPosition(position);
    
    hitbox.width = size.x;
    hitbox.height = size.y;

    setPosition(position);

    hitbox.left = position.x;
    hitbox.top = position.y;

    return true;
}

void Player::update (sf::Time dt) {
    if (state != State::dead && state !=State::dying) {
        position.x += speed*dt.asSeconds();
        if (position.x < 0 ||position.x > screenWidth + size.x){
            position.x -= speed*dt.asSeconds();
        }
        this->setPosition(position);
    } else {
        
    }
}

/*void Alien::changeState(bool isDead) {
    if (!isDead) {
        state = (state == one) ? two : one;
    }
}*/

/*Alien::State Alien::getState() {
    return this->state;
}

sf::Vector2f Alien::getPosition () {
    return position;
}

sf::Vector2i Alien::getSize() {
    return size;
}
*/

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

    // apply the texture
    states.texture = &shipTexture;

    // you may also override states.shader or states.blendMode if you want

    int inicio = (int) state * 4;
    int j = 0;
    for (int i = inicio; i < inicio + 4; i++){
        drawing[0][j] = shipVertexs[i];
        j++;
    }


    sf::RectangleShape r;
        r.setFillColor(sf::Color(255, 20, 50));
        r.setOutlineColor(sf::Color(100, 200, 100));
        r.setOutlineThickness(1);
        r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
        r.setPosition(hitbox.left, hitbox.top);
        //std::cout << size.x << " " << size.y << std::endl;
        target.draw(r);    

    // draw the vertex array
    target.draw(*drawing, states);
}