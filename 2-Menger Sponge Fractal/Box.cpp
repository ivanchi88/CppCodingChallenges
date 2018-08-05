#include "Box.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime> // To seed the generator.
#include <unistd.h>
#include <chrono>
#include <vector>

Box::Box(int width, int height, int pos) {
    windowWidth = width,
    windowHeight = height;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + pos;
    gen = std::mt19937_64(seed);
    randSpeed = std::uniform_real_distribution<double>(minSpeed, maxSpeed);
    randPos = std::uniform_int_distribution<int>(1, 4);
    ballDirection =  std::uniform_int_distribution<int> (0, 1);

    circle = new sf::CircleShape();
    circle->setFillColor(sf::Color(255, 255, 255));


    drawings = std::vector<sf::Shape*>();
    drawings.push_back(circle);
    drawings.push_back(new sf::RectangleShape(sf::Vector2f(trailLength, 1))); //rectangle
    drawings[1]->setFillColor(sf::Color(245, 245, 245));
    Box::init();
}

void Box::init() {

    drawings[1]->setRotation(0);

    do {  
        xSpeed = randSpeed(gen) ;
        xSpeed = ballDirection (gen) == 0 ? xSpeed : -xSpeed;
        ySpeed = randSpeed(gen);
        ySpeed = ballDirection (gen) == 0 ? ySpeed : -ySpeed;
    }
    while(ySpeed == 0 && xSpeed == 0);


    int xPos = windowWidth / 2;
    int yPos = windowHeight / 2;

    circle->setPosition(xPos, yPos);

    int displacement = randPos(gen);
    circle->move(xSpeed * displacement, ySpeed * displacement);
    changeSize(); 
    circle->setRadius(size);

    drawings[1]->setPosition(circle->getPosition().x , circle->getPosition().y + size );
    sf::RectangleShape* rect = (sf::RectangleShape*) (drawings[1]);
    rect->setSize(sf::Vector2f(trailLength * module() * 0.0025, 1));


    trailAngle = calculateTrailAngle();
    drawings[1]->rotate(180 + trailAngle);
}

void Box::update(sf::Time dt) {
    
    circle->move(xSpeed * dt.asSeconds() * (module() * accelFactor), ySpeed*dt.asSeconds() * (module() * accelFactor));
    drawings[1]->move(xSpeed * dt.asSeconds() * (module() * accelFactor), ySpeed*dt.asSeconds() * (module() * accelFactor));
    if (Box::isOutOfBorders()){
        Box::init();
    } else {
        changeSize();
    }
}

std::vector<sf::Shape*> Box::draw () {
    return drawings;
}

double Box::module () {
    return sqrt(pow(circle->getPosition().x - windowWidth/2, 2) + pow(circle->getPosition().y - windowHeight/2,2));
}

void Box::changeSize() {
    size = minSize + (Box::module() * reductionFactor);
    circle->setRadius(size);
}

bool Box::isOutOfBorders () {
    if (circle->getPosition().x < -size || circle->getPosition().x > windowWidth) 
        return true;
    if (circle->getPosition().y < -size || circle->getPosition().y > windowHeight)
        return true;
    return false;
}

 int Box::calculateTrailAngle(){
    return (std::atan2(ySpeed, xSpeed) * 180 / 3.1415);
 }