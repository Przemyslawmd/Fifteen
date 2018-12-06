
#include "Board.h"
#include "MappedValues.h"
#include <iterator>

using std::begin;
using std::end;
using std::distance;
using std::find;


Board* Board::createBoard( BoardSize boardSize )
{
    if ( board )
    {
        delete board;
    }

    board = new Board( boardSize );
    return board;
}

/*********************************************************************************/
/*********************************************************************************/

Board* Board::createBoard( vector< int >& values, BoardSize boardSize )
{
    if ( board )
    {
        delete board;
    }

    board = new Board( values, boardSize );
    return board;
}

/*********************************************************************************/
/*********************************************************************************/

Move Board::checkMove( int row, int col )
{        
    int size = Mapped::BoardSizeInt.at( boardSize );

    if ( row > 0 && ( values.at(( row - 1 ) * size + col ) == EMPTY_SQUARE ))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }

    if ( col < ( size - 1 ) && ( values.at( row * size + col + 1 ) == EMPTY_SQUARE ))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }

    if ( row < ( size - 1 ) && ( values.at(( row + 1 ) * size + col )  ==  EMPTY_SQUARE ))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }

    if ( col > 0 && ( values.at( row * size + col - 1 ) == EMPTY_SQUARE ))
    {
        makeMove( row, col, row, col -1 );
        return Move::LEFT;
    }

    return Move::NOT_ALLOWED;
}

/*********************************************************************************/
/*********************************************************************************/

vector< int >& Board::randomBoard()
{
    int emptyTill = findEmptyTill();
    int nullRow = emptyTill / 10;
    int nullCol = emptyTill % 10;
    int size = Mapped::BoardSizeInt.at( boardSize );

    Move move;
    QList< Move > moves;
    QTime time = QTime::currentTime();

    for ( int i = 0; i < 2000; i++ )
    {
        moves.clear();
        moves.append( Move::UP );
        moves.append( Move::RIGHT );
        moves.append( Move::DOWN );
        moves.append( Move::LEFT );
        move = moves.at( qrand() % moves.size() );

        while( true )
        {
            if (( move == Move::UP ) && ( nullRow > 0 ))
            {                
                makeMove( nullRow, nullCol, nullRow - 1, nullCol );
                nullRow--;
                break;
            }            

            if (( move == Move::RIGHT ) && ( nullCol < ( size - 1 )))
            {                
                makeMove( nullRow, nullCol, nullRow, nullCol + 1 );
                nullCol++;
                break;
            }            

            if (( move == Move::DOWN ) && ( nullRow < ( size - 1 )))
            {                
                makeMove( nullRow, nullCol, nullRow + 1, nullCol );
                nullRow++;
                break;
            }            

            if (( move == Move::LEFT ) && ( nullCol > 0 ))
            {                
                makeMove( nullRow, nullCol, nullRow, nullCol - 1 );
                nullCol--;
                break;
            }

            moves.removeOne( move );
            move = moves.at(( qrand() * static_cast< uint >( time.msec()) ) % moves.size() );
        }
    }

    return values;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::solveBoard()
{    
    values.clear();
    int size = Mapped::BoardSizeInt.at( boardSize );

    for ( int i = 1; i <= size * size; i++ )
    {
        values.push_back( i );
    }

    values.at( size * size - 1 ) = EMPTY_SQUARE;
}

/*********************************************************************************/
/*********************************************************************************/

BoardSize Board::getSize()
{
    return boardSize;
}

/*********************************************************************************/
/*********************************************************************************/

vector< int >& Board::sendBoard()
{
    return values;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

Board::Board( BoardSize boardSize )
{
    this->boardSize = boardSize;
    solveBoard();
}

/*********************************************************************************/
/*********************************************************************************/

Board::Board( vector< int >& values, BoardSize boardSize )
{
    this->values.clear();
    this->values = values;
    this->boardSize = boardSize;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    int size = Mapped::BoardSizeInt.at( boardSize );
    values.at( dstRow * size + dstCol ) += values.at( srcRow * size + srcCol );
    values.at( srcRow * size + srcCol ) = values.at( dstRow * size + dstCol ) - values.at( srcRow * size + srcCol );
    values.at( dstRow * size + dstCol ) -= values.at( srcRow * size + srcCol );
}

/*********************************************************************************/
/*********************************************************************************/

int Board::findEmptyTill()
{
    auto result = find( begin( values ), end( values ), EMPTY_SQUARE );
    int pos =  distance( begin( values ), result );
    int size = Mapped::BoardSizeInt.at( boardSize );
    return pos / size * 10 + pos % size;
}

/*********************************************************************************/
/*********************************************************************************/

Board* Board::board = nullptr;

