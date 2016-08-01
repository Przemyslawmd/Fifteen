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

/********************************************************************************************************/
/* RANDOM BOARD *****************************************************************************************/
/* It's to remeber - in case of normal move direction is randomed for clicked non empty square **********/
/* Here, direction is randomed for an empty square ******************************************************/

int** Board::randomBoard()
{
    int move = 0;    
    int remMove = 0;
    int nullRow = 0;
    int nullCol = 0;
    int const MOVECOUNT = 2000;

    QList<int> moves;

    moves << UP;
    moves << RIGHT;
    moves << DOWN;
    moves << LEFT;

    // Fiding an empty position
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
        // Restoring direct list
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

        // Increasing chance for move in left direction
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
                    randomAnotherMove( UP, &moves, &remMove, &move );
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
                    randomAnotherMove( RIGHT, &moves, &remMove, &move );
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
                    randomAnotherMove( DOWN, &moves, &remMove, &move );
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
                    randomAnotherMove( LEFT, &moves, &remMove, &move );
                    continue;
                }
            }
        }
    }

    return square;
}

/******************************************************************************************************/
/* RANDOM ANOTHER MOVE ********************************************************************************/

void Board::randomAnotherMove( int moveToExclude, QList<int>* moves, int* remMove, int* move )
{
    moves->removeOne( moveToExclude );
    *remMove = *remMove * 10 + moveToExclude;
    *move = moves->at( qrand() % moves->size() );
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

void Board::makeMove( int srcRow, int srcCol, int desRow, int desCol )
{
    int temp = square[desRow][desCol];
    square[desRow][desCol] = square[srcRow][srcCol];
    square[srcRow][srcCol] = temp;
}

