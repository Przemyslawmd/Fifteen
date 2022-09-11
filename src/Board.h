
#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Types.h"


class Board
{
public:

    Board( BoardSize );
    Board( std::vector< uint >& values, BoardSize );
    Board( const Board& ) = delete;

    Move checkMove( uint row, uint col );

    BoardSize getSize();
    std::vector< uint >& sendBoard();
    std::vector< uint >& randomBoard();
    void solveBoard();
    uint getEmptyTile();

private:

    void makeMove( uint srcRow, uint srcColumn, uint dstRow, uint dstColumn );
    uint findEmptyTill();

    const BoardSize size;
    const uint sizeInt;
    const uint emptyTile;

    std::vector< uint > values;
};

#endif

