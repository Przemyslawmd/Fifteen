
#ifndef BOARD_H
#define BOARD_H

#include <QList>

class Board
{

public:

    static Board* board;

    // Public methods for creating a board to ensure that only one instance of board may exist
    static Board* createBoard( int boardSize );
    static Board* createBoard( int** squareValues, int boardSize );

    // Check whether a move is allowed for an indicated row and column, if yes then make move
    int checkMove( int row, int col );

    // These methods return squares
    int** randomBoard();
    int** solveBoard();
    int** sendBoard();

private:

    int size;
    int** square;

    const int EMPTY = 0;    // Empty square

    enum Move { UP, RIGHT, DOWN, LEFT };

    // Constructors and destructor are invoked via createBoard
    Board( int boardSize );
    Board( int** squareValues, int boardSize );
    ~Board();

    // Make move swaping two squares
    void makeMove( int sourceRow, int sourceColumn, int destRow, int destColumn );

    int findNullSquare();
};

#endif // BOARD_H
