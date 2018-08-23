#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Cell.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 

int numberCells;
bool hasNeighboursUnvisited(std::vector<Cell*> *(&cells), Cell *(&cellAct));
bool checkNeighbour(std::vector<Cell*> *(&cells), int x, int y);
void generateMaze (std::vector<Cell*> *(&cells), Cell* &cellAct, sf::RenderWindow &target);
Cell* getRandNeightbour(std::vector<Cell*> *(&cells), int x, int y);
void breakWalls(Cell *&cellAct, Cell *&cellNeigh) ;

int t = 0;


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1000, height = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    /* Game variables*/
    sf::Clock clock;

    bool isPaused = false;

    std::vector<Cell*> *cells = new std::vector<Cell*>();
    int cellSize = 20;
    numberCells = width / cellSize;
    for (int i = 0; i < numberCells; i++) {
        for (int j = 0; j < numberCells; j++) {
            cells->push_back(new Cell(width, height, i, j, cellSize));
        }
    }

    Cell *cellAct = (*cells)[0];
    generateMaze(cells, cellAct, window);

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        window.clear(sf::Color(10, 10, 10));

        // Clear everything from the last frame
        /*     
        ****************************************
        Handle the players input
        ****************************************
        */

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            // window closed
            case sf::Event::Closed:
                window.close();
                break;
            // we don't process other types of events
            default:
                break;
            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            usleep(80000);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            isPaused = !isPaused;
            usleep(300000);
        }

        /*     
        ****************************************     
        Update the scene :)
        ****************************************     
        */

       if (!isPaused) {  
           /* Update the scene */

            // Draw our game scene here
            for (auto cell : *cells){
                cell->draw(window);
            }
            // Show everything we just drew
            window.display();
       }
    }
    return 0;
}

void generateMaze (std::vector<Cell*> *(&cells), Cell* &cellAct, sf::RenderWindow &target) {
    t++;
    cellAct->setVisited();

    Cell *cellNeig;
    while (hasNeighboursUnvisited(cells, cellAct)) {
        cellNeig = getRandNeightbour(cells, cellAct->getPosition().x, cellAct->getPosition().y);
        if (!cellNeig->getIsVisited()) {
            breakWalls(cellAct, cellNeig);
            /* drawing animation */
            cellAct->draw(target);
            cellNeig->draw(target);
            target.display();
            //usleep(1000);
            /* end drawing animation */
            generateMaze(cells, cellNeig, target);
        }
    }
    
}

void breakWalls(Cell *&cellAct, Cell *&cellNeigh) {
    int xAct, yAct, xNeig, yNeig;
    xAct = cellAct->getPosition().x;
    yAct = cellAct->getPosition().y;
    xNeig = cellNeigh->getPosition().x;
    yNeig = cellNeigh->getPosition().y;

    if (xAct != xNeig) {                    // Estan en distinta columna 
        if (xAct < xNeig) {                 // Romper pared dch Act y pared izq de Neigh
            cellAct->breakWall(1);
            cellNeigh->breakWall(3);
        } else {                            // Romper pared izq Act y pared dch de Neigh
            cellAct->breakWall(3);
            cellNeigh->breakWall(1);
        }
    } else { // Estan en distinta fila
        if (yAct < yNeig) {                 // Romper pared abj Act y pared arr Neigh
            cellAct->breakWall(2);
            cellNeigh->breakWall(0);
        } else {                            // Romper pared arr Act y pared abj Neigh
            cellAct->breakWall(0);
            cellNeigh->breakWall(2);
        }
    }
}

bool hasNeighboursUnvisited(std::vector<Cell*> *(&cells), Cell *(&cellAct)) {
    int x, y;
    x = cellAct->getPosition().x;
    y = cellAct->getPosition().y;
    
    if (checkNeighbour(cells, x + 1, y)) {
        return true;
    } 

    if (checkNeighbour(cells, x - 1, y)) {
        return true;
    } 

    if (checkNeighbour(cells, x , y + 1)) {
        return true;
    }

    if (checkNeighbour(cells, x, y - 1)) {
        return true;
    }
    return false;
}

bool checkNeighbour(std::vector<Cell*> *(&cells), int x, int y) {
    if ( (x >= 0 && x < numberCells) && (y >= 0 && y < numberCells)) {
        if (!(*cells)[y * (numberCells) + x]->getIsVisited()){
            return true;
        }
    }
    return false;
}

Cell* getRandNeightbour(std::vector<Cell*> *(&cells), int x, int y) {

    if (rand() % 2 == 0) { //Busca vecino en X
        if (x == 0) { //solo puede ser el vecino de la dch
            return (*cells)[ y * (numberCells) + x + 1 ];
        } else if (x == (numberCells-1)) { //solo puede ser el vecino de la izq
            return (*cells)[ y * (numberCells) + x - 1 ];
        } else { //random entre ambos vecinos
            int r = 1 + ((rand() % 2) * -2);
            return (*cells)[y * (numberCells) + x + r];
        }
    } else {
        if (y == 0) { //solo puede ser el vecino de abajo
            return (*cells)[ (y + 1) * (numberCells) + x];
        } else if (y == (numberCells-1)) { //solo puede ser el vecino de arriba
            return (*cells)[ (y - 1) * (numberCells) + x];
        } else { //random entre ambos vecinos
            int r = 1 + ((rand() % 2) * -2);
            return (*cells)[(y + r) * (numberCells) + x];
        }
    }
}

