
#ifndef DATATEST_H
#define DATATEST_H

#include "DataCommon.h"
#include "DataGraphic.h"
#include <map>

using std::map;

class Data
{
public:

    static DataCommon& getTestVector( int testNumber );
    static DataGraphic& getTestGraphic( int testNumber );

private:

    static map< int, DataCommon > dataCommon;
    static map< int, DataGraphic > dataGraphic;
};

#endif // DATATEST_H

