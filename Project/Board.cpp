
#include "Board.h"
#include <iterator>

using std::begin;
using std::end;
using std::distance;
using std::find;

/*********************************************************************************/
/* CREATE BOARD ******************************************************************/

Board* Board::createBoard( BoardSize boardSize )
{
    if ( board )
        delete board;

    board = new Board( boardSize );
    return board;
}

/*********************************************************************************/
/* CREATE BOARD FROM FILE ********************************************************/

Board* Board::createBoard( int** squareValues, BoardSize boardSize )
{
    if ( board )
        delete board;

    board = new Board( squareValues, boardSize );
    return board;
}


Board* Board::createBoard( unique_ptr< vector<int> > squareValues, BoardSize boardSize )
{
    if ( board )
        delete board;

    board = new Board( std::move( squareValues ), boardSize );
    return board;
}

/**********************************************************************************/
/* CONSTRUCTOR ********************************************************************/

Board::Board( BoardSize size )
{
    this->size = size;
    solveBoard();
}

/**********************************************************************************/
/* CONSTRUCTOR FOR A BOARD FROM A FILE ********************************************/

Board::Board( int** values, BoardSize size )
{
    this->values.clear();
    this->size = size;

    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
        {
            this->values.push_back( values[i][j] );
        }
    }
}

Board::Board( unique_ptr< vector<int> > values, BoardSize size )
{
    this->values.clear();
    this->size = size;

    for ( auto it = values->begin(); it != values->end(); it++ )
    {
        this->values.push_back( *it );
    }
}

/*************************************************************************************/
/* CHECK WHETHER MOVE IS POSSIBLE ****************************************************/

Move Board::checkMove( int row, int col )
{        
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

/***************************************************************************************/
/* RANDOM BOARD ************************************************************************/

vector<int>& Board::randomBoard()
{
    // Find an empty square
    int nullSquare = findNullSquare();

    // TODO - handle this exception
    if ( nullSquare == -1 )
        return values;

    int nullRow = nullSquare / 10;
    int nullCol = nullSquare % 10;

    Move move;
    QList<Move> moves;
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

            // Remove move which is not allowed and random once again
            moves.removeOne( move );
            move = moves.at(( qrand() * static_cast<uint>( time.msec()) ) % moves.size() );
        }
    }

    return values;
}

/******************************************************************************/
/* FIND NULL SQUARE ***********************************************************/

int Board::findNullSquare()
{
    auto result = find( begin( values ), end( values ), EMPTY_SQUARE );
    if ( result == end( values ))
    {
        return -1;
    }

    int pos =  distance( begin( values ), result );
    return pos / size * 10 + pos % size;;
}

/*******************************************************************************/
/* SOLVE BOARD *****************************************************************/

void Board::solveBoard()
{    
    values.clear();

    for ( int i = 1; i <= size * size; i++ )
    {
        values.push_back( i );
    }

    values.at( size * size - 1 ) = EMPTY_SQUARE;
}

/*******************************************************************************/
/* SEND BOARD ******************************************************************/

vector<int>& Board::sendBoard()
{
    return values;
}

/********************************************************************************/
/* MAKE MOVE ********************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    values.at( dstRow * size + dstCol ) += values.at( srcRow * size + srcCol );
    values.at( srcRow * size + srcCol ) = values.at( dstRow * size + dstCol ) - values.at( srcRow * size + srcCol );
    values.at( dstRow * size + dstCol ) -= values.at( srcRow * size + srcCol );
}

/********************************************************************************/
/* GET CURRENT SIZE *************************************************************/

BoardSize Board::getCurrentSize()
{
    return size;
}

/********************************************************************************/
/********************************************************************************/

Board* Board::board = nullptr;

