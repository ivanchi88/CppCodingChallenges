#include "Snake.hpp"
#include <cmath>
#include <iostream>
#include <random>
#include <ctime> // To seed the generator.
#include <unistd.h>
#include <chrono>
#include <vector>

Snake::Snake(int width, int height, int cellSiz, int snakeSiz) {
    if (snakeSiz < 1) {
        exit(1);
    }

    screenWidth = width;
    screenHeight = height;

    cellSize = cellSiz;
    cellNumber = width/cellSize;
    originalSnakeSize = snakeSiz;
    init ();
}

void Snake::init() {
    snakeSize = originalSnakeSize;
    body = std::vector<sf::Vector2<int>>();
    for (int i = 0; i < snakeSize; i++) {
        body.push_back(sf::Vector2<int>(0, 0));
    }
    speed.x = 1;
    speed.y = 0;
}

void Snake::update(sf::Vector2<int> *prize){
    sf::Vector2<int> newHead;
    newHead.x = body[0].x;
    newHead.y = body[0].y;

    newHead.x += speed.x;
    newHead.y += speed.y;

    /* Border Collitions */

    if (newHead.x < 0)
        newHead.x = cellNumber - 1;
    else
        if (newHead.x >= cellNumber)
            newHead.x = 0;

    if (newHead.y < 0)
        newHead.y = cellNumber - 1;
    else
        if (newHead.y >= cellNumber)
            newHead.y = 0;

    /* herself collition */
    if (checkCollitions(newHead)) {
        /* move the prize */
        prize->x = rand() % cellNumber-1;
        prize->y = rand() % cellNumber-1;
        /* restart snake */
        init();
    } else {

        /* picking prize */
        if (prize->x == newHead.x && prize->y == newHead.y) {
            std::cout << "prize! " << std::endl;
            body.push_back(sf::Vector2<int>(body[snakeSize-1].x, body[snakeSize-1].y));
            snakeSize++;
            prize->x = rand() % cellNumber-1;
            prize->y = rand() % cellNumber-1;
        }
    
        moveBody();
        body[0] = newHead;
    }
}

bool Snake::checkCollitions (sf::Vector2<int> newHead) {
    for (int i = 0; i < snakeSize-1; i++) {
        if (body[i].x == newHead.x && body[i].y == newHead.y) {
            std::cout << "dead! " << std::endl;
            return true;
        }
    }
    return false;
}

void Snake::moveBody() {
    for (int i = 1; i < snakeSize; i++) {
        body[snakeSize - i] = body[snakeSize - i-1];
    }
}

void Snake::move (int x, int y) {
    if (x != 0) {
        if (speed.x == 0) {
            speed.y = 0;            
            speed.x = x;
        }
    } else { 
        if (speed.y == 0) {
            speed.x = 0;
            speed.y = y;
        }
    }
}

std::vector<sf::RectangleShape*> Snake::draw () {
    std::vector<sf::RectangleShape*> drawing;
    int i = 0;
    for (auto cell : body) {
        sf::RectangleShape* cellR = new sf::RectangleShape();
        cellR->setPosition(cell.x * cellSize , cell.y * cellSize);
        cellR->scale(sf::Vector2f(0.95f, 0.95f));
        cellR->setSize(sf::Vector2f(cellSize, cellSize));
        if ( i == 0) {
            cellR->setFillColor(sf::Color(0, 50, 250));
        } else {
            cellR->setFillColor(sf::Color(100, 250, 50));
        }
        drawing.push_back(cellR);
        i++;
    }
    return drawing;
}

