
#ifndef FIFTEEN_BOARD_H
#define FIFTEEN_BOARD_H

#include "Types.h"

#include <vector>


class Board
{
public:

    Board( BoardSize, BoardMode mode );
    Board( std::vector< uint >& values, BoardSize, BoardMode mode );
    Board( const Board& ) = delete;
    Board operator=( const Board& ) = delete;

    Move checkMove( uint row, uint col );

    BoardSize getSize() const;
    uint getSizeInt() const;
    BoardMode getMode() const;
    void setMode( BoardMode );

    std::vector< uint >& sendValues();
    std::vector< uint >& randomBoard();
    void solveBoard();
    uint getEmptyTile();

private:

    void makeMove( uint srcRow, uint srcColumn, uint dstRow, uint dstColumn );
    uint findEmptyTill();

    const BoardSize size;
    const uint sizeInt;

    BoardMode mode;
    const uint emptyTile;

    std::vector< uint > values;
};

#endif

