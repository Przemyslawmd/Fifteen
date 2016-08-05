#include "Board.h"

/***********************************************************************************************************/
/* CONSTRUCTOR *********************************************************************************************/

Board::Board(int size)
{
    this->size = size;

    square = new int*[size];
    for (int i = 0; i < size; i++)
        square[i] = new int[size];

    int k = 1;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)        
            square[i][j] = k++;        
    }
    square[size-1][size-1] = EMPTY;
}

/********************************************************************************************************/
/* CONSTRUCTOR FOR A BOARD RESTORED FROM A FILE *********************************************************/

Board::Board(int** values, int size)
{
    this->size = size;

    square = new int*[size];
    for (int i = 0; i < size; i++)
        square[i] = new int[size];

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            square[i][j] = values[i][j];
    }
}

/********************************************************************************************************/
/* DESTRUCTOR *******************************************************************************************/

Board::~Board()
{
    for (int i = 0; i < size; i++)
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
/* In case of normal move ( trigerred by an user ) a direction is being randomed for clicked non empty square ***/
/* Here, direction is being randomed for an empty square ********************************************************/

int** Board::randomBoard()
{
    int move = 0;    
    int remMove = 0;
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
        // Restore a list with move directions
        if ( remMove != 0 )
        {
            if ( remMove < 10 )
                moves.append( remMove );
            else
            {
                moves.append( remMove / 10 );
                moves.append( remMove % 10 );
            }
            remMove = 0;
        }

        // Increase a chance for a move in a left direction
        if ( i % 5 == 0 )
           move = LEFT;
        else
           move = qrand() % LEFT + 1;  // randoming from 1 to 4

        while( true )
        {            
            // MOVE UP ///////////////////////////////////////////////
            if ( move == UP )
            {
                if ( nullRow > 0 )
                {
                    makeMove( nullRow, nullCol, nullRow - 1, nullCol );
                    nullRow--;
                    break;
                }
                else
                {
                    move = randomAnotherMove( UP, &moves, &remMove );
                    continue;
                }
            }            
            // MOVE RIGHT //////////////////////////////////////////////
            else if ( move == RIGHT )
            {
                if (nullCol < (size - 1))
                {
                    makeMove( nullRow, nullCol, nullRow, nullCol + 1 );
                    nullCol++;
                    break;
                }
                else
                {
                    move = randomAnotherMove( RIGHT, &moves, &remMove );
                    continue;
                }
            }            
            // MOVE DOWN /////////////////////////////////////////////////
            else if ( move == DOWN )
            {
                if (nullRow < (size - 1))
                {
                    makeMove( nullRow, nullCol, nullRow + 1, nullCol );
                    nullRow++;
                    break;
                }
                else
                {
                    move = randomAnotherMove( DOWN, &moves, &remMove );
                    continue;
                }
            }            
            // MOVE LEFT /////////////////////////////////////////////////
            else
            {
                if ( nullCol > 0 )
                {
                    makeMove( nullRow, nullCol, nullRow, nullCol - 1 );
                    nullCol--;
                    break;
                }
                else
                {
                    move = randomAnotherMove( LEFT, &moves, &remMove );
                    continue;
                }
            }
        }
    }

    return square;
}

/******************************************************************************************************/
/* RANDOM ANOTHER MOVE ********************************************************************************/

int Board::randomAnotherMove( int moveToExclude, QList<int>* moves, int* remMove)
{
    moves->removeOne( moveToExclude );
    *remMove = *remMove * 10 + moveToExclude;
    return moves->at( qrand() % moves->size() );
}

/*******************************************************************************************************/
/* RESTORE A BOARD TO INITIAL STATE ********************************************************************/

int** Board::solveBoard()
{
    int k = 1;
    for ( int i = 0; i < size; i++ )
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
/* MAKE MOVE ********************************************************************************************/

void Board::makeMove( int srcRow, int srcCol, int dstRow, int dstCol )
{    
    square[dstRow][dstCol] += square[srcRow][srcCol];
    square[srcRow][srcCol] = square[dstRow][dstCol] - square[srcRow][srcCol];
    square[dstRow][dstCol] -= square[srcRow][srcCol];
}

