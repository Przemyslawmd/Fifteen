
#ifndef DATATEST_H
#define DATATEST_H

#include "TestVector.h"
#include "TestVectorGraphic.h"

class Data
{

public:

    static void DataInit();

    static int getBoardSize( int testNumber );
    static vector< int > getMoves( int testNumber );
    static vector< int > getExpectedSquares( int testNumber );

    static TestGraphic& getTestGraphic( int testNumber );

private:

    static vector< TestVector > testData;
    static vector< TestGraphic > testDataGraphic;
};

#endif // DATATEST_H
