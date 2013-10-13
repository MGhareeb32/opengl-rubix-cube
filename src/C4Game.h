#ifndef GAME_H_
#define GAME_H_

#include <iostream>

class C4Game {
public:
    const static int W = 7, H = 6, SCORE = 5;
private:
    int disks, turn, winner;
    int **board;
    int *colHeight;
    int *score;

    int getWinner(int x, int y);
public:
    C4Game();
    void init();
    void resetScore();
    int play(int col);
    int getWinner();
    int getCurrentPlayer();
    int getColHeight(int col);
    int getScore(int player);
    int* operator[](int row);
    virtual ~C4Game();
};

#endif
