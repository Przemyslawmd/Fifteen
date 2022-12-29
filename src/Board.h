
#ifndef FIFTEEN_BOARD_H
#define FIFTEEN_BOARD_H

#include "Types.h"

#include <vector>


class Board
{
public:

    Board( BoardSize );
    Board( std::vector< uint >& values, BoardSize );
    Board( const Board& ) = delete;
    Board operator=( const Board& ) = delete;

    Move checkMove( uint row, uint col );

    BoardSize getSize();
    uint getSizeInt() const;

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

