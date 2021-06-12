
#ifndef UNDO_MOVE_H
#define UNDO_MOVE_H

#include <deque>
#include "Types.h"

constexpr int MOVE_STACK_EMPTY = 10000;


class UndoMove
{
public:

    UndoMove() = default;
    UndoMove( const UndoMove& ) = delete;
    UndoMove operator=( const UndoMove& ) = delete;

    void PutMove( Move move, uint row, uint col );
    uint GetMove();
    void Reset();

private:

    std::deque< uint > moveStack;
    const uint MOVE_STACK_LIMIT = 10;
};

#endif

