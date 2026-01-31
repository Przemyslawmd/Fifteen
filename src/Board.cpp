
#include "Board.h"

#include <iterator>
#include <numeric>

#include "MappedValues.h"


constexpr size_t emptyTile(size_t size) { return size * size - 1; }


Board::Board( BoardSize size, BoardMode mode ) : size{ size },
                                                 mode{ mode },
                                                 sizeInt{ Maps::boardSizeInt.at( size )}
{
    values.resize( sizeInt * sizeInt );
    std::iota( values.begin(), values.end(), 0 );
}

/*********************************************************************************/
/*********************************************************************************/

Board::Board( std::vector<size_t>&& values, BoardSize size, BoardMode mode ) : size{ size },
                                                                               mode{ mode },
                                                                               sizeInt{ Maps::boardSizeInt.at( size ) },
                                                                               values{ std::move( values )} {}

/*********************************************************************************/
/*********************************************************************************/

Move Board::checkMove( size_t row, size_t col )
{
    if ( row > 0 && ( values.at(( row - 1 ) * sizeInt + col ) == emptyTile( sizeInt )))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }
    if ( col < ( sizeInt - 1 ) && ( values.at( row * sizeInt + col + 1 ) == emptyTile( sizeInt )))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }
    if ( row < ( sizeInt - 1 ) && ( values.at(( row + 1 ) * sizeInt + col )  == emptyTile( sizeInt )))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }
    if ( col > 0 && ( values.at( row * sizeInt + col - 1 ) == emptyTile( sizeInt )))
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
    size_t emptyPosition = findEmptyPosition();
    size_t emptyRow = emptyPosition / 10;
    size_t emptyCol = emptyPosition % 10;

    std::vector<Move> moves( 4 );
    using enum Move;

    for ( int i = 0; i < 4000; i++ )
    {
        moves.clear();
        moves.insert( moves.begin(), { UP, RIGHT, DOWN, LEFT });
        Move move = moves.at( rand() % moves.size() );

        while( true )
        {
            if (( move == UP ) && ( emptyRow > 0 ))
            {
                makeMove( emptyRow, emptyCol, emptyRow - 1, emptyCol );
                emptyRow--;
                break;
            }
            if (( move == RIGHT ) && ( emptyCol < ( sizeInt - 1 )))
            {
                makeMove( emptyRow, emptyCol, emptyRow, emptyCol + 1 );
                emptyCol++;
                break;
            }
            if (( move == DOWN ) && ( emptyRow < ( sizeInt - 1 )))
            {
                makeMove( emptyRow, emptyCol, emptyRow + 1, emptyCol );
                emptyRow++;
                break;
            }
            if (( move == LEFT ) && ( emptyCol > 0 ))
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

size_t Board::getSizeInt() const
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

const std::vector<size_t>& Board::getBoardValues() const
{
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

size_t Board::getEmptyTile() const
{
    return emptyTile(sizeInt);
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void Board::makeMove( size_t srcRow, size_t srcCol, size_t dstRow, size_t dstCol )
{
    std::swap( values.at( dstRow * sizeInt + dstCol ), values.at( srcRow * sizeInt + srcCol ));
}

/*********************************************************************************/
/*********************************************************************************/

size_t Board::findEmptyPosition()
{
    uint nullValuePos =  std::distance( values.begin(), std::find( values.begin(), values.end(), emptyTile(sizeInt) ));
    return nullValuePos / sizeInt * 10 + nullValuePos % sizeInt;
}

