
#ifndef DATATEST_H
#define DATATEST_H

#include "DataCommon.h"
#include "DataGraphic.h"

class Data
{
public:

    static void DataInit();

    static DataCommon& getTestVector( int testNumber );
    static DataGraphic& getTestGraphic( int testNumber );

private:

    static bool isInit;
    static vector< DataCommon > dataCommon;
    static vector< DataGraphic > dataGraphic;
};

#endif // DATATEST_H

