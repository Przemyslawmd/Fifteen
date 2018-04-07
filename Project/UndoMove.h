
#ifndef UNDOMOVE_H
#define UNDOMOVE_H

#include <deque>

class UndoMove
{
public:

    UndoMove();

    void PutMove( int move );
    int GetMove();

private:

    std::deque< int > moveStack;
    const unsigned int MOVE_STACK_LIMIT = 10;
};

#endif // UNDOMOVE_H
