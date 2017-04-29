
#ifndef BOARD_H
#define BOARD_H

#include <QList>

const int EMPTY = 0;    // Empty square

enum move { UP = 1, RIGHT, DOWN, LEFT };

class Board
{

public:

    static Board* board;

    // Public methods for creating a board to ensure that only one instance of board may exist
    static Board* createBoard( int boardSize );
    static Board* createBoard( int** squareValues, int boardSize );

    // Check whether for provided row and column move is allowed
    // If yes then make move
    int checkMove( int row, int col );

    // These methods return squares
    int** randomBoard();
    int** solveBoard();
    int** sendBoard();    

private:

    int size;
    int** square;

    // Constructors and destructor are invoked via createBoard
    Board( int boardSize );
    Board( int** squareValues, int boardSize );
    ~Board();

    // Make move swaping rows and columns
    void makeMove( int sourceRow, int sourceColumn, int destRow, int destColumn );
};

#endif // BOARD_H
