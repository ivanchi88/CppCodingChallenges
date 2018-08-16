#include "Planet.hpp"

Planet::Planet(int width, int height):Planet(width, height, nullptr, 100 + rand() % 50, 0, 0){


}

Planet::Planet(int width, int height, sf::Vector2f *position, float parentRadius, int level, float distanceToParent_){
    screenWidth = width;
    screenHeight = height;
    asteroids = new std::vector<Planet*>();

    float radius = parentRadius * (1- (((rand() % 50) + 20) / 100.0));
    body = new sf::CircleShape(radius);

    if (position == nullptr) {
        position = new sf::Vector2f(width/2 - radius, height/2 - radius);
    }

    body->setPosition(*position);

    this->distanceToParent = distanceToParent_;

    parentPos = position;
    angle = 0;

    int xOffset;
    int i = 0;
    /* generar satelites */
    int maxLevels = 3;
    if (level < maxLevels) {
        while (rand() % 10 < 5 || (level == 0 && i == 0)) {
            //std::cout << "level " << level << " planet " << i << std::endl;
            xOffset = (radius*3 ) + (rand() % ((int)radius*2));
            asteroids->push_back(new Planet(width, height, new sf::Vector2f(xOffset + parentPos->x + radius*2, xOffset + parentPos->y + radius), radius, level + 1, xOffset));
            i++;
        }
    }
    speed = ((rand() % 200) + 100) / 100.0;
    speed = rand() % 2 == 0 ? -speed : speed;
}
void Planet::update(sf::Time dt, sf::Vector2f const &parentPos){
   angle += dt.asSeconds() * speed;
   
   float y2 = distanceToParent * sin(angle);
   y2 += parentPos.y;
   float x2 = distanceToParent * cos(angle);
   x2 += parentPos.x;

   for (auto asteroid : *asteroids){
       asteroid->update(dt, sf::Vector2f(x2 + body->getRadius(), y2 +  body->getRadius()));
   }

   body->setPosition(x2 + body->getRadius(), y2 + body->getRadius());
}

void Planet::rotate () {

}


void Planet::draw(sf::RenderWindow &target){
    target.draw(*body);
    for (auto asteroid : *asteroids) {
        asteroid->draw(target);
    }
}
Planet::~Planet(){
    if (parentPos != nullptr){
        delete parentPos;
    }
    if (body != nullptr) {
        delete body;
    }
    if (asteroids != nullptr) {
        for (auto asteroid : *asteroids) {
            if (asteroid != nullptr) {
                delete asteroid;
            }
        }

        delete asteroids;
    }
}

float Planet::getRadius () {
    return body->getRadius();
}