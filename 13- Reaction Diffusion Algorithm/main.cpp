#include <iostream>
#include <vector>
#include <random> 
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Cell.hpp"
#include <chrono> //For system_clock
#include <unistd.h>

#define assetsFolder "./resources/" 

const int height = 1000;
const int cellSize = 5;
const int numberCells = height / cellSize;

const float difusionA = 1.0, difusionB = 0.5, feed = 0.055, kill = 0.012;

void updateCells(Cell cells[numberCells][numberCells], sf::Time dt);
void updateCell(Cell cells[numberCells][numberCells], Cell cell, sf::Time dt);

int t = 0;


int main(int agrc, char *argv[])
{

    /* Window initialization */
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    int width = 1000;
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!",sf::Style::Default, settings);
    //sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    srand(time(NULL));

    /* Game variables*/
    sf::Clock clock;

    bool isPaused = false; 

    Cell cells [numberCells][numberCells];

    for (int i = 0; i < numberCells; i++) {
        for (int j = 0; j < numberCells; j++) {
            cells[i][j] = Cell (width, height, i, j, cellSize);
        }
    }

    /* Pequeño area de B = 1.0 */
    for (int i = 100; i < 110  ; i++) {
        for (int j = 100; j < 110; j++) {
            cells[i][j].setAB({0.0, 1.0});
            cells[i][j].setLastAB({0.0, 1.0});
        }
    }

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
            updateCells(cells, dt);
            // Draw our game scene here
            for (int i = 0; i < numberCells; i++) {
                for (int j = 0; j < numberCells; j++) {
                    cells[i][j].draw(window);
                }
            }
            // Show everything we just drew
            window.display();
            //std::cout << dt.asSeconds() << std::endl;
       }
    }
    return 0;
}

void updateCells(Cell cells[numberCells][numberCells], sf::Time dt) {
    for (int i = 0; i < numberCells; i++) {
        for (int j = 0; j < numberCells; j++){
            updateCell(cells, (cells)[i][j], dt);
            //std::cout << (cells)[i][j].getAB().x << " " << (cells)[i][j].getLastAB().x  << " " << (cells)[i][j].getAB().y << " " << (cells)[i][j].getLastAB().y << std::endl;
        }
    }
}

void updateCell(Cell cells[numberCells][numberCells], Cell cell, sf::Time dt){
    float totalA = 0.0;
    float totalB = 0.0;
    int cellX = cell.getPosition().x, cellY = cell.getPosition().y;
    if (cellX != 0) {
            totalA += (cells)[cellY][cellX - 1].getLastAB().x * 0.2; // A izquierda centro
            totalB += (cells)[cellY][cellX - 1].getLastAB().y * 0.2; // B izquierda centro
            if (cellY != 0){
                totalA += (cells)[cellY - 1][cellX - 1].getLastAB().x * 0.05; // A izquierda arriba
                totalB += (cells)[cellY - 1][cellX - 1].getLastAB().y * 0.05; // B izquierda arriba
            }
            if (cellY != numberCells-1){
                totalA += (cells)[cellY + 1][cellX - 1].getLastAB().x * 0.05; // A izquierda abajo
                totalB += (cells)[cellY + 1][cellX - 1].getLastAB().y * 0.05; // B izquierda abajo
            }
    }
    if (cellX != numberCells -1) {
            totalA += (cells)[cellY][cellX + 1].getLastAB().x * 0.2; // A derecha centro
            totalB += (cells)[cellY][cellX + 1].getLastAB().y * 0.2; // B derecha centro
            if (cellY != 0){
                totalA += (cells)[cellY - 1][cellX + 1].getLastAB().x * 0.05; // A derecha arriba
                totalB += (cells)[cellY - 1][cellX + 1].getLastAB().y * 0.05; // B derecha arriba
            }
            if (cellY != numberCells-1){
                totalA += (cells)[cellY + 1][cellX + 1].getLastAB().x * 0.05; // A derecha abajo
                totalB += (cells)[cellY + 1][cellX + 1].getLastAB().y * 0.05; // B derecha abajo
            }
    }

    if (cellY != 0) {
        totalA += (cells)[cellY - 1][cellX].getLastAB().x * 0.2; // A centro arriba
        totalB += (cells)[cellY - 1][cellX].getLastAB().y * 0.2; // B centro arriba
    }
    if (cellY != numberCells - 1) {
        totalA += (cells)[cellY + 1][cellX].getLastAB().x * 0.2; // A centro abajo
        totalB += (cells)[cellY + 1][cellX].getLastAB().y * 0.2; // B centro abajo
    }
    totalA -= cell.getLastAB().x; // A centro
    totalB -= cell.getLastAB().y; // B centro

    /* laplace * A  &&  B */
    totalA *= cell.getLastAB().x;
    totalB *= cell.getLastAB().y;

    /* difusion */
    totalA *= difusionA; 
    totalB *= difusionB;

    /* asimilamiento de 2 a en 1 b */
    totalA -= cell.getLastAB().x * cell.getLastAB().y * cell.getLastAB().y;  
    totalB += cell.getLastAB().x * cell.getLastAB().y * cell.getLastAB().y;

    /* ratio de alimento-muerte */
    totalA += feed * (1 - cell.getLastAB().x);
    totalB += - (kill + feed) * cell.getLastAB().y;

    /* A = A' + totalA * dt; B = B' + totalB * dt */
    cell.setAB({cell.getLastAB().x + (totalA) * 2.0, cell.getLastAB().y + (totalB) * 2.0});
}