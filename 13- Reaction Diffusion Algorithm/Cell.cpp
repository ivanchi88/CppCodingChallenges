#include "Cell.hpp"

Cell::Cell(int width, int height, int row, int col, int size){
    screenWidth = width;
    screenHeight = height;
    this->row = row;
    this->col = col;
    this->size = size;

    background = new sf::RectangleShape({size, size});
    background->setPosition({col * size, row * size});

    A = 1.0f;
    Aant = 1.0f;
    B = 0.0f;
    Bant = 0.0f;
}

sf::Vector2f Cell::getAB(){
    return  {A , B};
}

sf::Vector2f Cell::getLastAB(){
    return  {Aant , Bant};
}

void Cell::setAB(sf::Vector2f ab){
    A = ab.x;
    B = ab.y;
}

void Cell::setLastAB(sf::Vector2f ab){
    Aant = ab.x;
    Bant = ab.y;
}


void Cell::update(sf::Time dt){

}

sf::Vector2i Cell::getPosition() {
    return {col, row};
}

Cell::Cell () {
    
}



void Cell::draw(sf::RenderWindow &target){ 
    Aant = A;
    Bant = B;
    /* Background */
    float c = (A - B) * 255;

    background->setFillColor({c, c, c});
    target.draw(*background);

}

sf::RectangleShape* Cell::getBackground(){
    return background;
}
Cell::~Cell(){
    if (background != nullptr) {
        delete background;
    }

}
