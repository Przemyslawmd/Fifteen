
#include "Board.h"

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

/**********************************************************************************/
/* CONSTRUCTOR ********************************************************************/

Board::Board( BoardSize size )
{
    this->size = size;
    square = new int*[size];

    for ( int i = 0; i < size; i++ )
        square[i] = new int[size];

    solveBoard();
}

/**********************************************************************************/
/* CONSTRUCTOR FOR A BOARD FROM A FILE ********************************************/

Board::Board( int** values, BoardSize size )
{
    this->size = size;
    square = new int*[size];

    for ( int i = 0; i < size; i++ )
    {
        square[i] = new int[size];
        for ( int j = 0; j < size; j++ )
            square[i][j] = values[i][j];
    }
}

/************************************************************************************/
/* DESTRUCTOR ***********************************************************************/

Board::~Board()
{
    for ( int i = 0; i < size; i++ )
        delete[] square[i];

    delete[] square;
}

/*************************************************************************************/
/* CHECK WHETHER MOVE IS POSSIBLE ****************************************************/

Move Board::checkMove( int row, int col )
{        
    if ( row > 0 && ( square[row - 1][col] == EMPTY_SQUARE ))
    {
        makeMove( row, col, row - 1, col );
        return Move::UP;
    }

    if ( col < ( size - 1 ) && ( square[row][col + 1] == EMPTY_SQUARE ))
    {
        makeMove( row, col, row, col + 1 );
        return Move::RIGHT;
    }

    if ( row < ( size - 1 ) && ( square[row + 1][col] ==  EMPTY_SQUARE ))
    {
        makeMove( row, col, row + 1, col );
        return Move::DOWN;
    }

    if ( col > 0 && ( square[row][col -1] == EMPTY_SQUARE ))
    {
        makeMove( row, col, row, col -1 );
        return Move::LEFT;
    }

    return Move::NOT_ALLOWED;
}

/***************************************************************************************/
/* RANDOM BOARD ************************************************************************/

int** Board::randomBoard()
{
    // Find an empty square
    int nullSquare = findNullSquare();

    // Only in case of same error
    if ( nullSquare == -1 )
        return nullptr;

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

    return square;
}

/******************************************************************************/
/* FIND NULL SQUARE ***********************************************************/

int Board::findNullSquare()
{
    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
        {
            if ( square[i][j] == EMPTY_SQUARE )
                return i * 10 + j;
        }
    }

    return -1;
}

/*******************************************************************************/
/* SOLVE BOARD *****************************************************************/

void Board::solveBoard()
{    
    for ( int i = 0, k = 1; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
            square[i][j] = k++;        
    }
    square[size-1][size-1] = EMPTY_SQUARE;
}

/*******************************************************************************/
/* SEND BOARD VALUES ***********************************************************/

int** Board::sendBoard()
{
    return square;
}

/********************************************************************************/
/* MAKE MOVE ********************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    square[dstRow][dstCol] += square[srcRow][srcCol];
    square[srcRow][srcCol] = square[dstRow][dstCol] - square[srcRow][srcCol];
    square[dstRow][dstCol] -= square[srcRow][srcCol];
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

