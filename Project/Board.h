
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <QList>
#include <QTime>

class Board
{

public:

    static Board* board;

    // Methods to create a board and to ensure that only one instance of board may exist
    static Board* createBoard( int boardSize );
    static Board* createBoard( int** values, int boardSize );

    // Check whether move is allowed
    Move checkMove( int row, int col );

    int getCurrentSize();
    int** randomBoard();
    int** sendBoard();
    void solveBoard();

private:

    int size;
    int** square;
    const int EMPTY_SQUARE = 0;

    // Constructors and destructor are invoked via createBoard
    Board( int boardSize );
    Board( int** values, int boardSize );
    ~Board();

    // Make move by swaping two squares
    void makeMove( int sourceRow, int sourceColumn, int destRow, int destColumn );

    int findNullSquare();
};

#endif // BOARD_H
