#include "Blob.hpp"

Blob::Blob(int width, int height){
    screenWidth = width;
    screenHeight = height;
    radius = rand() % 100 + 100;

    position = new sf::Vector2f(rand()%(width - radius) + radius, rand() % (height - radius) + radius);
    speed = new sf::Vector2f(rand()%300 - 200, rand() % 300  - 200);
    while(speed->x == 0 || speed->y == 0) {
        speed->x = rand()%300 - 200;
        speed->y = rand()%300 - 200;
    }
}


void Blob::update(sf::Time dt){
    *position += *speed * dt.asSeconds();
    if (position->x < 0 ||position->x > screenWidth) {
        speed->x = - speed->x;
    }
    if (position->y < 0 ||position->y > screenHeight) {
        speed->y = - speed->y;
    }
}

sf::Vector2f Blob::getPosition() {
    return *position;
}

float Blob::getRadius() {
    return radius;
}

Blob::~Blob(){
    if (position != nullptr){
        delete position;
    }
    if (speed != nullptr) {
        delete speed;
    }

}
