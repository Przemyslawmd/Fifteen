
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <vector>

using std::vector;

class Board
{
public:

    static Board* createBoard( BoardSize );
    static Board* createBoard( vector< int >& values, BoardSize );

    Move checkMove( int row, int col );

    BoardSize getSize();
    int getIntSize();

    vector< int >& sendBoard();
    vector< int >& randomBoard();
    void solveBoard();

    static Board* board;

private:

    Board( BoardSize );
    Board( vector< int >& values, BoardSize );

    void makeMove( int srcRow, int srcColumn, int dstRow, int dstColumn );
    int findEmptyTill();

    const BoardSize boardSize;
    vector< int > values;
    const int EMPTY_SQUARE = 0;
};

#endif // BOARD_H

