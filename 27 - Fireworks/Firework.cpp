#include "Firework.hpp"

Firework::Firework(int width, int height){
    screenWidth = width;
    screenHeight = height;
    size =  5 + rand () % 5;
    position = new sf::Vector2f(rand() % (width - size) + size, height + rand () % 500);
    speed = 600 + rand() % 300;
    bodyParts = rand() % 2 + 3;
    color = new sf::Color(rand() % 250 , rand() % 250 , rand() % 250);

    body = new std::vector<sf::RectangleShape*>;
    for (int i = 0; i < bodyParts; i++) {
        body->push_back(new sf::RectangleShape({(size - i*2), (size - i*2)}));
        (*body)[i]->setPosition(position->x + (i), (position->y + (i * (15 + size))));
        (*body)[i]->setFillColor(*color);
    }

    sparks = new std::vector<Spark*>();
    for (int i = 0; i < Spark::maxSparks; i++){
        sparks->push_back(new Spark());
    }
    isFirstExplosion = true;
}

void Firework::restart () {
    size =  2 + rand () % 5;
    position->x = rand() % (screenWidth - size) + size;
    position->y = screenHeight + rand() % 500;

    color->r = rand() % 250 ;
    color->g = rand() % 250 ;
    color->b = rand() % 250 ;

    speed = 600 + rand() % 300;

    for (int i = 0; i < bodyParts; i++) {
        (*body)[i]->setPosition(position->x + (i), (position->y + (i * (15 + size))));
        (*body)[i]->setFillColor(*color);
    }

    isFirstExplosion = true;

}

void Firework::update(sf::Time dt){
    if (speed > 80) {
        if (position->y <= screenHeight) {
            speed -= (400 + rand() % 200) * dt.asSeconds();
        }
        int i = 0;
        for (auto cell : *body) {
            cell->move(0, -speed * dt.asSeconds() - (i * 10) * dt.asSeconds() );
            i++;
        }
        position->y = (*body)[0]->getPosition().y;
    } else {
        if (speed > 0) {
            if (isFirstExplosion) {
                int i = 0;
                for (auto spark : *sparks) {
                    spark->restart(position->x, position->y, (*body)[0]->getFillColor(), i);
                    i++;
                }
                isFirstExplosion = false;
            } 
            for (auto spark : *sparks) {
                spark->update(dt);
            }
            speed -= 60 * dt.asSeconds();
            position->y -= speed * dt.asSeconds();
        } else {
            this->restart();
        }
    }
}

void Firework::draw(sf::RenderWindow &target){
    if (speed > 80) {
        for (auto cell : *body) {
            target.draw(*cell);
        }
    } else {
        for (auto spark : *sparks) {
            spark->draw(target);
        }
    }
    
}

Firework::~Firework(){
   /* if (sparks != nullptr){
        for (auto spark : *sparks) {
            delete spark;
        }
        delete sparks;
    }*/
    if (body != nullptr) {
        for (auto cell : *body) {
            delete cell;
        }   
        delete body;
    }

    if (position != nullptr) {
        delete position;
    }

}
