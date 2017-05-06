#include "Data.h"

int* Data::getMoves( int dataNumber )
{
    return moves[dataNumber];
}


int* Data::getExcpectedBoard( int dataNumber )
{
    return expectedBoard[dataNumber];
}


// In case of an array with moves a first digit means number of moves.
// Other digits mean trying to move, for example '23' means clicking in a square of a second row and a third column.
// Rows and colums have an array convention, they begin with zero value

int Data::moves_1[] = { 13, 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 };

int Data::moves_2[] = { 20, 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 };

int* Data::moves[] { moves_1, moves_2 };


int Data::expectedBoard_1[] { 1, 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 15, 13, 14, 12, 11 };

int Data::expectedBoard_2[] { 6, 1, 2, 4, 5, 7, 12, 3, 8, 9, 11, 17, 13, 14, 10, 21, 16, 18, 19, 15, 22, 0, 23, 24, 20 };

int* Data::expectedBoard[] { expectedBoard_1, expectedBoard_2 };
