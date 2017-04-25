#include "Board.h"

/***********************************************************************************************************/
/* CONSTRUCTOR *********************************************************************************************/

Board::Board( int size )
{
    this->size = size;

    square = new int*[size];
    for ( int i = 0; i < size; i++ )
        square[i] = new int[size];

    solveBoard();
}

/********************************************************************************************************/
/* CONSTRUCTOR FOR A BOARD RESTORED FROM A FILE *********************************************************/

Board::Board( int** values, int size )
{
    this->size = size;

    square = new int*[size];
    for ( int i = 0; i < size; i++ )
        square[i] = new int[size];

    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
            square[i][j] = values[i][j];
    }
}

/********************************************************************************************************/
/* DESTRUCTOR *******************************************************************************************/

Board::~Board()
{
    for ( int i = 0; i < size; i++ )
        delete[] square[i];

    delete[] square;
}

/********************************************************************************************************/
/* CHECK WHETHER MOVE IS POSSIBLE ***********************************************************************/

int Board::checkMove( int row, int col )
{        
    if ( row > 0 && (square[row - 1][col] == EMPTY ))
    {
        makeMove( row, col, row - 1, col );
        return UP;
    }

    if ( col < (size - 1) && (square[row][col + 1] == EMPTY ))
    {
        makeMove( row, col, row, col + 1 );
        return RIGHT;
    }

    if ( row < (size - 1) && (square[row + 1][col] ==  EMPTY ))
    {
        makeMove( row, col, row + 1, col );
        return DOWN;
    }

    if ( col > 0 && (square[row][col -1] == EMPTY ))
    {
        makeMove( row, col, row, col -1 );
        return LEFT;
    }

    return 0;
}

/****************************************************************************************************************/
/* RANDOM BOARD *************************************************************************************************/

int** Board::randomBoard()
{
    int move = 0;
    int removedMoves = 0;
    int nullRow = 0;
    int nullCol = 0;
    int const MOVECOUNT = 2000;

    QList<int> moves ( { UP, RIGHT, DOWN, LEFT } );

    // Find an empty square
    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
        {
            if ( square[i][j] == EMPTY )
            {
                nullRow = i;
                nullCol = j;
                break;
            }
        }
    }

    for ( int i = 0; i < MOVECOUNT; i++ )
    {
        // Restore list with all directions
        if ( removedMoves != 0 )
        {
            if ( removedMoves < 10 )
                moves.append( removedMoves );
            else
            {
                moves.append( removedMoves / 10 );
                moves.append( removedMoves % 10 );
            }
            removedMoves = 0;
        }

        // Increase a chance for move in a left direction
        if ( i % 5 == 0 )
           move = LEFT;
        else
           move = qrand() % LEFT + 1;  // random from 1 to 4

        while( true )
        {
            if (( move == UP ) && ( nullRow > 0 ))
            {                
                makeMove( nullRow, nullCol, nullRow - 1, nullCol );
                nullRow--;
                break;
            }            

            if (( move == RIGHT ) && ( nullCol < ( size - 1 )))
            {                
                makeMove( nullRow, nullCol, nullRow, nullCol + 1 );
                nullCol++;
                break;
            }            

            if (( move == DOWN ) && ( nullRow < (size - 1 )))
            {                
                makeMove( nullRow, nullCol, nullRow + 1, nullCol );
                nullRow++;
                break;
            }            

            if (( move == LEFT ) && ( nullCol > 0 ))
            {                
                makeMove( nullRow, nullCol, nullRow, nullCol - 1 );
                nullCol--;
                break;
            }

            moves.removeOne( move );
            removedMoves = removedMoves * 10 + move;
            move = moves.at( qrand() % moves.size() );
        }
    }

    return square;
}

/*******************************************************************************************************/
/* SET A BOARD TO ITS INITIAL STATE ********************************************************************/

int** Board::solveBoard()
{    
    for ( int i = 0, k = 1; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
            square[i][j] = k++;        
    }
    square[size-1][size-1] = EMPTY;

    return square;
}

/********************************************************************************************************/
/* SEND BOARD VALUES ************************************************************************************/

int** Board::sendBoard()
{
    return square;
}

/********************************************************************************************************/
/* COMMIT MOVE ******************************************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    square[dstRow][dstCol] += square[srcRow][srcCol];
    square[srcRow][srcCol] = square[dstRow][dstCol] - square[srcRow][srcCol];
    square[dstRow][dstCol] -= square[srcRow][srcCol];
}

