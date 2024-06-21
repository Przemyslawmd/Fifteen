
#ifndef FIFTEEN_UNDO_MOVE_H
#define FIFTEEN_UNDO_MOVE_H

#include <deque>
#include <optional>

#include "Types.h"


class UndoMove
{
public:

    UndoMove() = default;
    UndoMove( const UndoMove& ) = delete;
    UndoMove operator=( const UndoMove& ) = delete;

    void PutMove( Move move, size_t row, size_t col );
    std::optional<size_t> GetMove();
    void Reset();

private:

    std::deque<size_t> moveStack;
    const size_t MOVE_STACK_LIMIT = 10;
};

#endif

