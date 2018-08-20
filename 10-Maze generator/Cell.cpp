#include "Cell.hpp"

Cell::Cell(int width, int height, int row, int col, int size){
    screenWidth = width;
    screenHeight = height;
    this->row = row;
    this->col = col;
    this->size = size;

    walls = new sf::VertexArray (sf::LinesStrip, 2);
    background = new sf::RectangleShape({size, size});
    background->setPosition({col * size, row * size});
    background->setFillColor({50, 20, 100, 120});

    isVisited = false;
}


void Cell::update(sf::Time dt){

}

sf::Vector2i Cell::getPosition() {
    return {col, row};
}

void Cell::setVisited(){
    isVisited = true;
    background->setFillColor({0, 200, 100});
}

bool Cell::getIsVisited() {
    return isVisited;
}

void Cell::breakWall(int index){
    wall[index] = false;
}


void Cell::draw(sf::RenderWindow &target){

    /* Background */
    target.draw(*background);

    /* top */
    if (wall[0]) {
        (*walls)[0].position = {col * size, row * size };
        (*walls)[0].color = {255, 255, 255};
        (*walls)[1].position = {col * size + size, row * size};
        (*walls)[1].color = {255, 255, 255};
        target.draw(*walls);
    }


    /* right */
    if (wall[1]) {
        (*walls)[0].position = {col * size + size, row * size };
        (*walls)[0].color = {255, 255, 255};
        (*walls)[1].position = {col * size + size, row * size + size};
        (*walls)[1].color = {255, 255, 255};
        target.draw(*walls);
    }

    /* bottom */
    if (wall[2]) {
        (*walls)[0].position = {col * size, row * size + size };
        (*walls)[0].color = {255, 255, 255};
        (*walls)[1].position = {col * size + size, row * size + size};
        (*walls)[1].color = {255, 255, 255};
        target.draw(*walls);
    }

    /* left */
    if (wall[3]) {
        (*walls)[0].position = {col * size, row * size};
        (*walls)[0].color = {255, 255, 255};
        (*walls)[1].position = {col * size , row * size + size};
        (*walls)[1].color = {255, 255, 255};
        target.draw(*walls);
    }
}

sf::RectangleShape* Cell::getBackground(){
    return background;
}
Cell::~Cell(){
    if (walls != nullptr){
        delete walls;
    }
    if (background != nullptr) {
        delete background;
    }

}
