
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

    vector< int >& sendBoard();
    vector< int >& randomBoard();
    void solveBoard();
    int getEmptyTile();

    static Board* board;

private:

    Board( BoardSize,  int sizeInt );
    Board( vector< int >& values, BoardSize, int sizeInt );

    void makeMove( int srcRow, int srcColumn, int dstRow, int dstColumn );
    int findEmptyTill();

    const BoardSize size;
    const int sizeInt;
    const int emptyTile;

    vector< int > values;
};

#endif

