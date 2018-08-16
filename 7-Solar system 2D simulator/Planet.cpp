#include "Planet.hpp"

Planet::Planet(int width, int height):Planet(width, height, nullptr, 50 + rand() % 50){}
Planet::Planet(int width, int height, sf::Vector2f *position, float radius){
    
}
void Planet::update(sf::Time dt){
   
}


sf::CircleShape* Planet::draw(){

}
Planet::~Planet(){

}