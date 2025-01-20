
#include "UndoMove.h"

constexpr size_t MOVE_STACK_LIMIT = 10;


void UndoMove::PutMove( Move move, size_t row, size_t col )
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
    }
}

/*********************************************************************************/
/*********************************************************************************/

std::optional<size_t> UndoMove::GetMove()
{
    if ( moveStack.empty() )
    {
        return std::nullopt;
    }

    size_t move = moveStack.back();
    moveStack.pop_back();
    return move;
}

/*********************************************************************************/
/*********************************************************************************/

void UndoMove::Reset()
{
    moveStack.clear();
}

