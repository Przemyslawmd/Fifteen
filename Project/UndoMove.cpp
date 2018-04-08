
#include "UndoMove.h"

void UndoMove::PutMove( Move move, int row, int col )
{
    if ( moveStack.size() == MOVE_STACK_LIMIT )
    {
        moveStack.pop_front();
    }

    switch ( move )
    {
        case UP:
            moveStack.push_back(( row - 1 ) * 10 + col );
            break;
        case RIGHT:
            moveStack.push_back( row * 10 + col + 1 );
            break;
        case DOWN:
            moveStack.push_back(( row + 1 ) * 10 + col );
            break;
        case LEFT:
            moveStack.push_back( row * 10 + col -1  );
            break;
    }
}

/*********************************************************************************/
/*********************************************************************************/

int UndoMove::GetMove()
{
    if ( moveStack.empty() )
    {
        return -1;
    }

    int move = moveStack.back();
    moveStack.pop_back();
    return move;
}

/*********************************************************************************/
/*********************************************************************************/

void UndoMove::Reset()
{
    if ( moveStack.empty() == false )
    {
        moveStack.clear();
    }
}

