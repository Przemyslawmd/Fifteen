
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <QList>
#include <array>

using std::array;

class Board
{

public:

    static Board* board;

    // Methods to create a board and to ensure that only one instance of board may exist
    static Board* createBoard( int boardSize );
    static Board* createBoard( int** squareValues, int boardSize );

    // Check whether move is allowed, if yes then make move
    Move checkMove( int row, int col );

    int** randomBoard();
    int** sendBoard();
    void solveBoard();

private:

    int size;
    int** square;
    const int EMPTY = 0;    // Empty square    

    // Constructors and destructor are invoked via createBoard
    Board( int boardSize );
    Board( int** squareValues, int boardSize );
    ~Board();

    // Make move by swaping two squares
    void makeMove( int sourceRow, int sourceColumn, int destRow, int destColumn );

    int findNullSquare();
};

#endif // BOARD_H
