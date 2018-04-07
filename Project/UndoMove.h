
#ifndef UNDOMOVE_H
#define UNDOMOVE_H

#include "Types.h"
#include <deque>

class UndoMove
{
public:

    void PutMove( Move move, int row, int col );
    int GetMove();
    void Reset();

private:

    std::deque< int > moveStack;
    const unsigned int MOVE_STACK_LIMIT = 10;
};

#endif // UNDOMOVE_H
