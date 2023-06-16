#include "Game.h"
#include <windows.h>
#include <iostream>

int main() {
    char choice;
    do {
        int difficulty;
        std::cout << "type difficulty level, affects only speed of snake:\n";
        std::cout << "1 - Easy \n";
        std::cout << "2 - Medium\n";
        std::cout << "3 - Hard\n";
        std::cout << "choice: ";
        std::cin >> difficulty;
        Game snake;
        snake.setDifficulty(difficulty);
        while (!snake.isGameOver()) {
            snake.draw();
            snake.getKeyToMove();
            snake.move();
            Sleep(snake.getSlowDown()); // in milliseconds
        }

        system("cls");
        std::cout << "snake over! Your result is: " << snake.getScore() << std::endl;

        std::fstream scoreFile("scores.txt", std::ios::in | std::ios::out | std::ios::app);
        if (scoreFile.is_open()) {
            scoreFile << snake.getScore() << "\n";
            scoreFile.close();
        } else {
            std::cout << "Unable to open file";
        }

        std::cout << "start new game? (y/n): ";
        std::cin >> choice;

    } while (choice == 'y' || choice == 'Y');
    displayScores();
    return 0;
}
