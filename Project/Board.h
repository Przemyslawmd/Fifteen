
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <vector>

using std::vector;

class Board
{
public:

    Board( BoardSize );
    Board( vector< uint >& values, BoardSize );

    Move checkMove( uint row, uint col );

    BoardSize getSize();

    vector< uint >& sendBoard();
    vector< uint >& randomBoard();
    void solveBoard();
    uint getEmptyTile();

    static Board* board;

private:

    void makeMove( uint srcRow, uint srcColumn, uint dstRow, uint dstColumn );
    uint findEmptyTill();

    const BoardSize size;
    const uint sizeInt;
    const uint emptyTile;

    vector< uint > values;
};

#endif

