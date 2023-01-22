
#include "Board.h"
#include "MappedValues.h"

#include <iterator>
#include <numeric>


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

Board::Board( std::vector< uint >& values, BoardSize size, BoardMode mode ) : size( size ),
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

std::vector< uint >& Board::randomBoard()
{
    uint emptyTillPos = findEmptyTill();
    uint nullRow = emptyTillPos / 10;
    uint nullCol = emptyTillPos % 10;

    std::vector< Move > moves( 4 );

    for ( int i = 0; i < 4000; i++ )
    {
        moves.clear();
        moves.push_back( Move::UP );
        moves.push_back( Move::RIGHT );
        moves.push_back( Move::DOWN );
        moves.push_back( Move::LEFT );
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

            std::remove( moves.begin(), moves.end(), move );
            move = moves[ rand() % moves.size() ];
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

BoardSize Board::getSize() const
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

std::vector< uint >& Board::sendValues()
{
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::getNullValue()
{
    return emptyTile;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void Board::makeMove( uint srcRow, uint srcCol, uint dstRow, uint dstCol )
{    
    std::swap( values.at( dstRow * sizeInt + dstCol ), values.at( srcRow * sizeInt + srcCol ));
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::findEmptyTill()
{
    auto empty = std::find( values.begin(), values.end(), emptyTile );
    uint emptyPos =  std::distance( values.begin(), empty );
    return emptyPos / sizeInt * 10 + emptyPos % sizeInt;
}

