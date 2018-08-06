#include "Drop.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime> // To seed the generator.
#include <unistd.h>
#include <chrono>
#include <vector>

Drop::Drop(int width, int height, int pos) {
    screenWidth = width;
    screenHeight = height;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count() + pos;

    gen = std::mt19937_64(seed);
    randSpeed = std::uniform_real_distribution<double>(minSpeed, maxSpeed);
    randPos = std::uniform_int_distribution<int>(0, screenWidth);

    body = new sf::RectangleShape();
    body->setFillColor(sf::Color(180, 10, 255));
    p = pos;

    init ();
}

void Drop::init () {
    
    speed = randSpeed(gen);

    size.x =  1 + (speed / minSpeed);
    size.y =  5 + (speed / minSpeed)*3;

    std::cout << size.x << " " << size.y << std::endl;
    body->setSize(size);
    body->setPosition(randPos(gen), -randPos(gen));

}

void Drop::update (sf::Time dt) {

    body->move(0, speed * dt.asSeconds());
    speed += dt.asSeconds();

    if (body->getPosition().y > screenHeight) {
        init();
    }
}

sf::RectangleShape Drop::draw () {
    return *body;
}

