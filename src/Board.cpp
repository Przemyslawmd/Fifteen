
#include "Board.h"
#include "MappedValues.h"

#include <QList>
#include <QTime>

#include <iterator>

using std::vector;


Board::Board( BoardSize size, BoardMode mode ) : size( size ),
                                                 mode( mode ),
                                                 sizeInt( Maps::boardSizeInt.at( size )),
                                                 emptyTile( sizeInt * sizeInt - 1 )
{
    values.resize( sizeInt * sizeInt );
    std::iota( values.begin(), values.end(), 0 );
}

/*********************************************************************************/
/*********************************************************************************/

Board::Board( vector< uint >& values, BoardSize size, BoardMode mode ) : size( size ),
                                                                         mode( mode ),
                                                                         sizeInt( Maps::boardSizeInt.at( size )),
                                                                         emptyTile( sizeInt * sizeInt - 1 )
{
    this->values.clear();
    this->values = values;
}

/*********************************************************************************/
/*********************************************************************************/

Move Board::checkMove( uint row, uint col )
{        
    if ( row > 0 && ( values.at(( row - 1 ) * sizeInt + col ) == emptyTile ))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }

    if ( col < ( sizeInt - 1 ) && ( values.at( row * sizeInt + col + 1 ) == emptyTile ))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }

    if ( row < ( sizeInt - 1 ) && ( values.at(( row + 1 ) * sizeInt + col )  == emptyTile ))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }

    if ( col > 0 && ( values.at( row * sizeInt + col - 1 ) == emptyTile ))
    {
        makeMove( row, col, row, col -1 );
        return Move::LEFT;
    }

    return Move::NOT_ALLOWED;
}

/*********************************************************************************/
/*********************************************************************************/

vector< uint >& Board::randomBoard()
{
    uint emptyTillPos = findEmptyTill();
    uint nullRow = emptyTillPos / 10;
    uint nullCol = emptyTillPos % 10;

    QList< Move > moves;
    QTime time = QTime::currentTime();

    for ( int i = 0; i < 2000; i++ )
    {
        moves.clear();
        moves.append( Move::UP );
        moves.append( Move::RIGHT );
        moves.append( Move::DOWN );
        moves.append( Move::LEFT );
        Move move = moves.at( rand() % moves.size() );

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

            moves.removeOne( move );
            move = moves.at(( rand() * static_cast< uint >( time.msec()) ) % moves.size() );
        }
    }

    return values;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::solveBoard()
{    
    std::sort( values.begin(), values.end() );
}

/*********************************************************************************/
/*********************************************************************************/

BoardSize Board::getSize()
{
    return size;
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::getSizeInt() const
{
    return sizeInt;
}

/*********************************************************************************/
/*********************************************************************************/

BoardMode Board::getMode() const
{
    return mode;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::setMode( BoardMode mode )
{
    this->mode = mode;
}

/*********************************************************************************/
/*********************************************************************************/

vector< uint >& Board::sendBoard()
{
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::getEmptyTile()
{
    return emptyTile;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void Board::makeMove( uint srcRow, uint srcCol, uint dstRow, uint dstCol )
{    
    values.at( dstRow * sizeInt + dstCol ) += values.at( srcRow * sizeInt + srcCol );
    values.at( srcRow * sizeInt + srcCol ) =  values.at( dstRow * sizeInt + dstCol ) - values.at( srcRow * sizeInt + srcCol );
    values.at( dstRow * sizeInt + dstCol ) -= values.at( srcRow * sizeInt + srcCol );
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::findEmptyTill()
{
    auto result = std::find( std::begin( values ), std::end( values ), emptyTile );
    uint pos =  std::distance( std::begin( values ), result );
    return pos / sizeInt * 10 + pos % sizeInt;
}

