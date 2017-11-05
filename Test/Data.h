
#ifndef DATATEST_H
#define DATATEST_H

#include "TestVector.h"

class Data
{

public:

    static int getBoardSize( int testNumber );
    static vector< int > getMoves( int testNumber );
    static vector< int > getExpectedSquares( int testNumber );

private:

    static vector< TestVector > testData;
};

#endif // DATATEST_H
