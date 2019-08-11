
#ifndef DATATEST_H
#define DATATEST_H

#include "DataGraphic.h"
#include <map>

using std::map;

class Data
{
public:

    static DataGraphic& getTestGraphic( int testNumber );

private:

    static map< int, DataGraphic > dataGraphic;
};

#endif // DATATEST_H

