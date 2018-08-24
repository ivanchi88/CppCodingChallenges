#include "Spark.hpp"

Spark::Spark(){
    position = new sf::Vector2f();
    body = new sf::RectangleShape({rand()%3, rand()%3});
    speed = new sf::Vector2f();
    color = new sf::Color(0, 0, 0);
}

void Spark::restart(int x, int y, sf::Color color, int n) {

    speed->x = (20 + rand() % 150) * ((n < Spark::maxSparks / 4) || (n > ( 3 * Spark::maxSparks/4)) ? 1  : -1);
    speed->y = (20 + rand() % 150) * ((n < Spark::maxSparks / 2) ? 1 : -1);


    position->x = x;
    position->y = y;
    body->setFillColor(color);

    this->color->r = body->getFillColor().r;
    this->color->g = body->getFillColor().g;
    this->color->b = body->getFillColor().b;
    this->color->a = body->getFillColor().a;
    body->setPosition(*position);
}

void Spark::update(sf::Time dt){
    body->move(*speed * dt.asSeconds());
    speed->x += ((speed->x > 0) ? -1.0 : 1.0) * 5.0 * dt.asSeconds() ;
    speed->y += 5 * dt.asSeconds();

    color->a =  color->a - (dt.asSeconds()/10);
    body->setFillColor(*color);

}
void Spark::draw(sf::RenderWindow& target){
    target.draw(*body);
}
Spark::~Spark(){
    
}