#ifndef BOARD_H
#define BOARD_H

#include <QList>

const int EMPTY = 0;    // Empty square

const int UP = 1;
const int RIGHT = 2;
const int DOWN = 3;
const int LEFT = 4;

class Board
{

public:
    Board(int);
    Board(int**, int);
    ~Board();
    int checkMove(int, int);
    int** randomBoard();
    int** solveBoard();
    int** sendBoard();    

private:
    int size;
    int** square;

    void makeMove(int, int, int, int);
    int randomAnotherMove( int, QList<int>&, int* );
};

#endif // BOARD_H
