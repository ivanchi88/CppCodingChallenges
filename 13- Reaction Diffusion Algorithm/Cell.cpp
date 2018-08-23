#include "Cell.hpp"

Cell::Cell(int width, int height, int row, int col, int size){
    screenWidth = width;
    screenHeight = height;
    this->row = row;
    this->col = col;
    size = size;
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

void Cell::setAB(float a, float b){
    A = a;
    B = b;
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

float constraint2(float n) {
    if (n >= 0.0 && n <= 255.0 ) {
        return n;
    }
    return (n < 0.0) ? 0.0 : 255.0;
}

void Cell::draw(sf::RenderWindow &target){
    //std::cout << A << " " << Aant << "   " << B << " " << Bant<< std::endl;
    Aant = A;
    Bant = B;
    /* Background */
    float c = constraint2((A - B)  * 255);

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
