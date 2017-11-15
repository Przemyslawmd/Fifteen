
#ifndef DATATEST_H
#define DATATEST_H

#include "TestVector.h"
#include "TestVectorGraphic.h"

class Data
{

public:

    static void DataInit();

    static TestVector& getTestVector( int testNumber );
    static TestGraphic& getTestGraphic( int testNumber );

private:

    static bool isInit;
    static vector< TestVector > testData;
    static vector< TestGraphic > testDataGraphic;
};

#endif // DATATEST_H
