
#include "UndoMove.h"

void UndoMove::PutMove( Move move, uint row, uint col )
{
    if ( moveStack.size() == MOVE_STACK_LIMIT )
    {
        moveStack.pop_front();
    }

    switch ( move )
    {
        case Move::UP:
            moveStack.push_back(( row - 1 ) * 10 + col );
            break;
        case Move::RIGHT:
            moveStack.push_back( row * 10 + col + 1 );
            break;
        case Move::DOWN:
            moveStack.push_back(( row + 1 ) * 10 + col );
            break;
        case Move::LEFT:
            moveStack.push_back( row * 10 + col -1  );
            break;
         default:
            break;
    }
}

/*********************************************************************************/
/*********************************************************************************/

uint UndoMove::GetMove()
{
    if ( moveStack.empty() )
    {
        return MOVE_STACK_EMPTY;
    }

    uint move = moveStack.back();
    moveStack.pop_back();
    return move;
}

/*********************************************************************************/
/*********************************************************************************/

void UndoMove::Reset()
{
    moveStack.clear();
}

