#include "game.h"


Game::Game() {
    this->gameOver = false;
    this->direction = STOP;
    this->xHead = boardWidth / 2;
    this->yHead = boardHeight / 2;
    srand(time(NULL));
    this->xFood = 1 + rand() % boardWidth;
    this->yFood = 1 + rand() % boardHeight;
    this->result = 0;
}


void Game::draw() {
    system("cls");
    std::cout << "w a s d to move\n x to close\n" << std::endl;
    for (int i = 0;
         i < boardHeight + 2; i++) {
        for (int j = 0;
             j < boardWidth + 2; j++) {
            if (i == 0 || i == boardHeight + 1 || j == 0 || j == boardWidth + 1)
                std::cout << 'X';
            else if (j == xHead && i == yHead)
                std::cout << '@';
            else if (j == xFood && i == yFood)
                std::cout << '*';
            else {
                bool lengthAdd = false;
                for (int k = 1; k <= length; k++) {
                    if (j == xLength[k] && i == yLength[k]) {
                        std::cout << 'o';
                        lengthAdd = true;
                    }
                }
                if (!lengthAdd)
                    std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    std::cout << "\nScore: " << result << std::endl;
}


void Game::getKeyToMove() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                direction = LEFT;
                break;
            case 's':
                direction = DOWN;
                break;
            case 'w':
                direction = UP;
                break;
            case 'd':
                direction = RIGHT;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Game::move() {
    xLength[0] = xHead;
    yLength[0] = yHead;
    for (int i = length; i > 0; i--) {
        xLength[i] = xLength[i - 1];
        yLength[i] = yLength[i - 1];
    }

    switch (direction) {
        case LEFT:
            xHead--;
            break;
        case RIGHT:
            xHead++;
            break;
        case UP:
            yHead--;
            break;
        case DOWN:
            yHead++;
            break;
    }

    if (xHead <= 0)
        xHead = boardWidth;
    else if (xHead >= boardWidth + 1)
        xHead = 1;
    else if (yHead <= 0)
        yHead = boardHeight;
    else if (yHead >= boardHeight + 1)
        yHead = 1;

    if (xHead == xFood && yHead == yFood) {
        result++;
        srand(time(NULL));
        xFood = 1 + rand() % boardWidth;
        yFood = 1 + rand() % boardHeight;
        length++;
        if (speed > 0)
            speed--;
    }

    for (int j = 1; j <= length; j++) {
        if (xHead == xLength[j] && yHead == yLength[j])
            gameOver = true;
    }
}

bool Game::isGameOver() {
    return this->gameOver;
}

int Game::getSlowDown() {
    return speed;
}

int Game::getScore() {
    return result;
}

void displayScores() {
    std::vector<int> scores;
    std::ifstream scoreFile("scores.txt");


    if (scoreFile.is_open()) {
        std::istream_iterator<int> start(scoreFile), end;
        scores.insert(scores.begin(), start, end);
        scoreFile.close();
    } else {
        std::cout << "Unable to open file";
    }


    std::sort(scores.begin(), scores.end());


    std::cout << "Best scores: " << std::endl;
    int start = scores.size() > 10 ? scores.size() - 10 : 0;
    for (int i = start; i < scores.size(); i++) {
        std::cout << scores[i] << std::endl;
    }
}

void Game::setDifficulty(int difficulty) {
    switch (difficulty) {
        case 1:
            speed = 70;
            break;
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 30;
            break;
        default:
            speed = 50;
            break;
    }
}