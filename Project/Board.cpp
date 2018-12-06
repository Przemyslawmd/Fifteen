
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
    if ( row > 0 && ( values.at(( row - 1 ) * sizeInt + col ) == EMPTY_SQUARE ))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }

    if ( col < ( sizeInt - 1 ) && ( values.at( row * sizeInt + col + 1 ) == EMPTY_SQUARE ))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }

    if ( row < ( sizeInt - 1 ) && ( values.at(( row + 1 ) * sizeInt + col )  ==  EMPTY_SQUARE ))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }

    if ( col > 0 && ( values.at( row * sizeInt + col - 1 ) == EMPTY_SQUARE ))
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
    int nullSquare = findNullSquare();
    int nullRow = nullSquare / 10;
    int nullCol = nullSquare % 10;

    Move move;
    QList< Move > moves;
    QTime time = QTime::currentTime();

    // Random 2000 times a direction to move a null square
    for ( int i = 0; i < 2000; i++ )
    {
        // Restore list with all move directions
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

            if (( move == Move::RIGHT ) && ( nullCol < ( sizeInt - 1 )))
            {                
                makeMove( nullRow, nullCol, nullRow, nullCol + 1 );
                nullCol++;
                break;
            }            

            if (( move == Move::DOWN ) && ( nullRow < ( sizeInt - 1 )))
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

            // Remove move which is not allowed and random once again
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

    for ( int i = 1; i <= sizeInt * sizeInt; i++ )
    {
        values.push_back( i );
    }

    values.at( sizeInt * sizeInt - 1 ) = EMPTY_SQUARE;
}

/*********************************************************************************/
/*********************************************************************************/

BoardSize Board::getCurrentSize()
{
    return size;
}

/*********************************************************************************/
/*********************************************************************************/

vector< int >& Board::sendBoard()
{
    return values;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

Board::Board( BoardSize size )
{
    this->size = size;
    this->sizeInt = Mapped::BoardSizeInt.at( size );
    solveBoard();
}

/*********************************************************************************/
/*********************************************************************************/

Board::Board( vector< int >& values, BoardSize size )
{
    this->values.clear();
    this->values = values;
    this->size = size;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    values.at( dstRow * sizeInt + dstCol ) += values.at( srcRow * sizeInt + srcCol );
    values.at( srcRow * sizeInt + srcCol ) = values.at( dstRow * sizeInt + dstCol ) - values.at( srcRow * sizeInt + srcCol );
    values.at( dstRow * sizeInt + dstCol ) -= values.at( srcRow * sizeInt + srcCol );
}

/*********************************************************************************/
/*********************************************************************************/

int Board::findNullSquare()
{
    auto result = find( begin( values ), end( values ), EMPTY_SQUARE );
    int pos =  distance( begin( values ), result );
    return pos / sizeInt * 10 + pos % sizeInt;
}

/*********************************************************************************/
/*********************************************************************************/

Board* Board::board = nullptr;

