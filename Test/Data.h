
#ifndef DATATEST_H
#define DATATEST_H

#include "DataCommon.h"
#include "DataGraphic.h"
#include "DataUndo.h"

class Data
{

public:

    static void DataInit();

    static DataCommon& getTestVector( int testNumber );
    static DataGraphic& getTestGraphic( int testNumber );
    static DataUndo& getTestUndo( int testNumber );

private:

    static bool isInit;
    static vector< DataCommon > dataCommon;
    static vector< DataGraphic > dataGraphic;
    static vector< DataUndo > dataUndo;
};

#endif // DATATEST_H
