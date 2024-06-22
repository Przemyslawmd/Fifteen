
#ifndef FIFTEEN_BOARD_H
#define FIFTEEN_BOARD_H

#include <vector>

#include "Types.h"


class Board
{
public:

    Board( BoardSize, BoardMode mode );
    Board( std::vector<size_t>&& values, BoardSize, BoardMode mode );
    Board( const Board& ) = delete;
    Board( Board&& ) = delete;
    Board& operator=( const Board& ) = delete;
    Board& operator=( Board&& ) = delete;

    Move checkMove( size_t row, size_t col );

    BoardSize getSize() const;
    uint getSizeInt() const;
    BoardMode getMode() const;
    void setMode( BoardMode );

    std::vector<size_t>& getBoardValues();
    void generateBoard();
    void solveBoard();

    uint getNullValue();

private:

    void makeMove( size_t srcRow, size_t srcColumn, size_t dstRow, size_t dstColumn );
    uint findEmptyTilePosition();

    const BoardSize size;
    const size_t sizeInt;

    BoardMode mode;
    const size_t nullValue;

    std::vector<size_t> values;
};

#endif

