#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <iterator>

enum move {
    STOP, UP, LEFT, DOWN, RIGHT
};

class Game {
private:
    bool gameOver;
    static const int boardWidth = 30;
    static const int boardHeight = 15;
    static const int board = boardWidth * boardHeight;
    int xHead, yHead, xFood, yFood, result;
    move direction;
    int xLength[board], yLength[board];
    int length = 0;
    int speed = 50;

public:
    Game();

    void draw();

    void getKeyToMove();

    void move();

    bool isGameOver();

    int getSlowDown();

    int getScore();

    void setDifficulty(int difficulty);
};

void displayScores();

#endif // GAME_H
