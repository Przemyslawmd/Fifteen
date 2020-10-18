
#ifndef UNDOMOVE_H
#define UNDOMOVE_H

#include "Types.h"
#include <deque>

#define MOVE_STACK_EMPTY 10000

class UndoMove
{
public:

    UndoMove() = default;
    UndoMove( const UndoMove& ) = delete;

    void PutMove( Move move, uint row, uint col );
    uint GetMove();
    void Reset();

private:

    std::deque< uint > moveStack;
    const unsigned int MOVE_STACK_LIMIT = 10;
};

#endif

