
#include "UndoMove.h"

UndoMove::UndoMove()
{

}

/*******************************************************************************************/
/*******************************************************************************************/

void UndoMove::PutMove( int position )
{
    if ( moveStack.size() == MOVE_STACK_LIMIT )
    {
        moveStack.pop_front();
    }

    moveStack.push_back( position );
}

/*******************************************************************************************/
/*******************************************************************************************/

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

