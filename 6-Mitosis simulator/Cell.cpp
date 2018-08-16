#include "Cell.hpp"

Cell::Cell(int width, int height):Cell(width, height, nullptr, 50 + rand() % 50){}
Cell::Cell(int width, int height, sf::Vector2f *position, float radius){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + (rand() % 500);
    gen = new std::mt19937_64(seed);
    randSpeed = new std::uniform_real_distribution<float>(0, maxSpeed);

    
    screenWidth = width;
    screenHeight = height;
    
    body = new sf::CircleShape(radius);
    if (position == nullptr) {
        position = new sf::Vector2f();
        randPosition = new std::uniform_real_distribution<float>(0, width);
        position->x = (*randPosition)(*gen);
        delete randPosition;
        randPosition = new std::uniform_real_distribution<float>(0, height);
        position->y = (*randPosition)(*gen);
    }

    body->setPosition(*position);
    
    speed = new sf::Vector2f( (*randSpeed)(*gen) - maxSpeed/2, (*randSpeed)(*gen)- maxSpeed/2);

    body->setFillColor(sf::Color(180, 20, 180, 120));
}
void Cell::update(sf::Time dt){
    body->move((*speed * dt.asSeconds()));
    if (rand() % 10000 < 5) {
        speed->x = (*randSpeed)(*gen) - maxSpeed/2;
        speed->y = (*randSpeed)(*gen) - maxSpeed/2;
    }
}
bool Cell::containsPoint(sf::Vector2f *point){
    float radius = body->getRadius();
    float dx = point->x - (body->getPosition().x + radius);
    float dy = (screenHeight - point->y) -  (screenHeight - (body->getPosition().y + radius));
    if ( dx * dx +  dy * dy < radius*radius ) {
        body->setRadius(radius * 0.8);
        body->move((rand() % 30) -15, (rand() % 30) -15);
        return true;
    }
    return false;
}
sf::Vector2f Cell::getPosition(){
    return body->getPosition();
}
float Cell::getSize(){
    return body->getRadius();
}
sf::CircleShape* Cell::draw(){
    return body;
}
Cell::~Cell(){
    if ( gen !=  nullptr) {
        delete gen;
    }
    if ( randSpeed !=  nullptr) {
        delete randSpeed;
    }
    if ( randPosition !=  nullptr) {
        delete randPosition;
    }
    if ( speed !=  nullptr) {
        delete speed;
    }
    if ( body !=  nullptr) {
        delete body;
    }
}