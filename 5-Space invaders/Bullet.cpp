#include "Bullet.hpp"

Bullet::Bullet(int width, int height){
    screenWidth = width;
    screenHeight = height;
    isRunning = false;
    size.x = width / 100;
    size.y = height / 25;
}

bool Bullet::loadTexture (sf::Texture &styleSheet) {

    bulletTexture = styleSheet;
    bulletVertexs.setPrimitiveType(sf::Quads);
    bulletVertexs.resize(12); /* First state, second and diying */

    //First state
    bulletVertexs[0].position = sf::Vector2f(0, 0);
    bulletVertexs[1].position = sf::Vector2f(1, 0);
    bulletVertexs[2].position = sf::Vector2f(1, 1);
    bulletVertexs[3].position = sf::Vector2f(0, 1);

    // define its 4 texture coordinates
    bulletVertexs[0].texCoords = sf::Vector2f(110, 23);
    bulletVertexs[1].texCoords = sf::Vector2f(116, 23);
    bulletVertexs[2].texCoords = sf::Vector2f(116, 42);
    bulletVertexs[3].texCoords = sf::Vector2f(110, 42);

    setScale(size.x , size.y);
    
    return true;
}

void Bullet::shoot(float oriX, float oriY, int direction) {
    if (!isRunning) {
        position.x = oriX - size.x/2; 
        position.y = oriY;
        speed = direction * 500;
        isRunning = true;
        hitbox.left = position.x;
        hitbox.width = size.x;
        hitbox.top = position.y;
        hitbox.height = size.y;
    }
}

void Bullet::update (sf::Time dt, std::vector<Shooteable*> &objetives) {
    if (isRunning) {
        position.y += speed * dt.asSeconds();
        hitbox.top = position.y;

        this->setPosition(position);
        if (position.y + size.y < 0 || position.y > screenHeight) {
            isRunning = false;
        } else {
            int pos = 0;
            for (auto objetive : objetives){
                if (objetive->getHitbox().intersects(this->hitbox)){
                    objetive->kill();
                    objetives.erase(objetives.begin() + pos);
                    isRunning = false;
                    std::cout << objetives.size() << std::endl;
                    break;
                }
                pos++;
            }
        }
        if (turn > 300) {
            scale(sf::Vector2f(-1,  1));
            turn = 0;
        }  
        turn++;
    }
}

sf::Rect<float> Bullet::getHitbox() {
    return hitbox;
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    if (isRunning) {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
        // apply the texture
        states.texture = &bulletTexture;

        sf::RectangleShape r;
        r.setFillColor(sf::Color(255, 20, 50));
        r.setOutlineColor(sf::Color(100, 200, 100));
        r.setOutlineThickness(1);
        r.setSize(sf::Vector2f(hitbox.width, hitbox.height));
        r.setPosition(hitbox.left, hitbox.top);
        //std::cout << size.x << " " << size.y << std::endl;
        //target.draw(r);       

        // draw the vertex array
        target.draw(bulletVertexs, states);
    }
}

void Bullet::kill () {
    std::cout << " Bullet " << std::endl;
}