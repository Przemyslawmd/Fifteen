#include "Data.h"

int* Data::getMoves( int dataNumber )
{
    if ( dataNumber == 1 )
        return moves_1;

    return nullptr;
}


int* Data::getExcpectedBoard( int dataNumber )
{
    if ( dataNumber == 1 )
        return expectedBoard_1;

    return nullptr;
}


// First number means number of moves
int Data::moves_1[] = { 3, 23, 23, 22 };

int Data::expectedBoard_1[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0, 11, 13, 14, 15, 12 };
