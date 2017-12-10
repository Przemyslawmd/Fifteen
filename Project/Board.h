
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <QList>
#include <QTime>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Board
{

public:

    static Board* board;

    // Methods to create a board and to ensure that only one instance of board may exist
    static Board* createBoard( BoardSize );
    static Board* createBoard( unique_ptr< vector<int> > values, BoardSize );

    // Check whether move is allowed
    Move checkMove( int row, int col );

    BoardSize getCurrentSize();
    vector<int>& sendBoard();
    vector<int>& randomBoard();
    void solveBoard();

private:

    BoardSize size;
    vector<int> values;
    const int EMPTY_SQUARE = 0;

    Board( BoardSize );
    Board( unique_ptr< vector<int> > values, BoardSize );

    // Make move by swaping two squares
    void makeMove( int sourceRow, int sourceColumn, int destRow, int destColumn );

    int findNullSquare();
};

#endif // BOARD_H
