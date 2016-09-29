#ifndef BOARD_H
#define BOARD_H

#include <QList>

const int EMPTY = 0;    // Empty square

enum move { UP = 1, RIGHT, DOWN, LEFT };

class Board
{

public:
    Board( int );
    Board( int**, int );
    ~Board();
    int checkMove( int, int );
    int** randomBoard();
    int** solveBoard();
    int** sendBoard();    

private:
    int size;
    int** square;

    void makeMove( int, int, int, int );
};

#endif // BOARD_H
