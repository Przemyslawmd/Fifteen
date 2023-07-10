
#include "Board.h"
#include "MappedValues.h"

#include <iterator>
#include <numeric>


Board::Board( BoardSize size, BoardMode mode ) : size( size ),
                                                 mode( mode ),
                                                 sizeInt( Maps::boardSizeInt.at( size )),
                                                 nullValue( sizeInt * sizeInt - 1 )
{
    values.resize( sizeInt * sizeInt );
    std::iota( values.begin(), values.end(), 0 );
}

/*********************************************************************************/
/*********************************************************************************/

Board::Board( std::vector< uint >&& values, BoardSize size, BoardMode mode ) : size( size ),
                                                                               mode( mode ),
                                                                               sizeInt( Maps::boardSizeInt.at( size )),
                                                                               values( values ),
                                                                               nullValue( sizeInt * sizeInt - 1 ) {}

/*********************************************************************************/
/*********************************************************************************/

Move Board::checkMove( uint row, uint col )
{        
    if ( row > 0 && ( values.at(( row - 1 ) * sizeInt + col ) == nullValue ))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }
    if ( col < ( sizeInt - 1 ) && ( values.at( row * sizeInt + col + 1 ) == nullValue ))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }
    if ( row < ( sizeInt - 1 ) && ( values.at(( row + 1 ) * sizeInt + col )  == nullValue ))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }
    if ( col > 0 && ( values.at( row * sizeInt + col - 1 ) == nullValue ))
    {
        makeMove( row, col, row, col -1 );
        return Move::LEFT;
    }

    return Move::NOT_ALLOWED;
}

/*********************************************************************************/
/*********************************************************************************/

void Board::generateBoard()
{
    uint emptyTile = findEmptyTilePosition();
    uint emptyRow = emptyTile / 10;
    uint emptyCol = emptyTile % 10;

    std::vector< Move > moves( 4 );

    for ( int i = 0; i < 4000; i++ )
    {
        moves.clear();
        moves.insert( moves.begin(), { Move::UP, Move::RIGHT, Move::DOWN, Move::LEFT });
        Move move = moves.at( rand() % moves.size() );

        while( true )
        {
            if (( move == Move::UP ) && ( emptyRow > 0 ))
            {                
                makeMove( emptyRow, emptyCol, emptyRow - 1, emptyCol );
                emptyRow--;
                break;
            }            
            if (( move == Move::RIGHT ) && ( emptyCol < ( sizeInt - 1 )))
            {                
                makeMove( emptyRow, emptyCol, emptyRow, emptyCol + 1 );
                emptyCol++;
                break;
            }            
            if (( move == Move::DOWN ) && ( emptyRow < ( sizeInt - 1 )))
            {                
                makeMove( emptyRow, emptyCol, emptyRow + 1, emptyCol );
                emptyRow++;
                break;
            }            
            if (( move == Move::LEFT ) && ( emptyCol > 0 ))
            {                
                makeMove( emptyRow, emptyCol, emptyRow, emptyCol - 1 );
                emptyCol--;
                break;
            }

            std::remove( moves.begin(), moves.end(), move );
            move = moves[ rand() % moves.size() ];
        }
    }
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

std::vector< uint >& Board::getBoardValues()
{
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::getNullValue()
{
    return nullValue;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void Board::makeMove( uint srcRow, uint srcCol, uint dstRow, uint dstCol )
{    
    std::swap( values.at( dstRow * sizeInt + dstCol ), values.at( srcRow * sizeInt + srcCol ));
}

/*********************************************************************************/
/*********************************************************************************/

uint Board::findEmptyTilePosition()
{
    uint nullValuePos =  std::distance( values.begin(), std::find( values.begin(), values.end(), nullValue ));
    return nullValuePos / sizeInt * 10 + nullValuePos % sizeInt;
}

