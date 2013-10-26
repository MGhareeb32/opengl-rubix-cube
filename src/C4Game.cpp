#include "C4Game.h"

C4Game::C4Game() {
    turn = 0;
    board = new int*[H];
    for(int i = 0; i < H; ++i)
        board[i] = new int[W];
    colHeight = new int[W];
    score = new int[3];
    resetScore();
    init();
}

void C4Game::init() {
    if (winner == -1) {
        score[1]++, score[2]++;
        turn = 3 - winner;
    } else if (winner) {
        score[winner]++;
    }
    winner = 0;
    disks = 0;
    for (int j = 0; j < W; ++j)
        colHeight[j] = 0;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            board[i][j] = 0;
}

void C4Game::resetScore() {
    for (int i = 0; i < 3; ++i)
        score[i] = 0;
}

int C4Game::play(int col) {
    int x = col;
    if (colHeight[x] == H)
        return -1;
    int y = H - colHeight[x] - 1;
    board[y][x] = (turn % 2) + 1;
    turn++;
    disks++;
    colHeight[x]++;
    return winner = getWinner(x, y);
}

int C4Game::getWinner(int x, int y) {
    int cell = board[y][x];
    int dir[8][2] = { {+1, 0}, {+1, -1}, {0, +1}, {-1, +1},
                      {-1, 0}, {-1, -1}, {0, -1}, {+1, +1} };
    for (int i = 0; i < 8; ++i) {
        int xx = x, yy = y;
        int dx = dir[i][0], dy = dir[i][1];
        int j = 0;
        while (xx >= 0 && xx < W && yy >= 0 && yy < H
               && board[yy][xx] == cell) {
            xx += dx, yy += dy, j++;
        }
        if (j >= 4)
            return cell;
    }
    return disks == W * H ? -1 : 0;
}

int C4Game::getWinner() {
    return winner;
}

int C4Game::getCurrentPlayer() {
    return (turn % 2) + 1;
}

int C4Game::getColHeight(int col) {
    return colHeight[col];
}

int C4Game::getScore(int player) {
    return score[player];
}

int* C4Game::operator[](int row) {
    return board[row];
}

C4Game::~C4Game() {
    for(int i = 0; i < H; ++i)
        delete[] board[i];
    delete[] board;
    delete[] colHeight;
}
