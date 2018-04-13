
#ifndef DATACOMMON_H
#define DATACOMMON_H

#include <vector>
#include "../Project/Types.h"

using std::vector;

class DataCommon
{

public:

    DataCommon( BoardSize boardSize, vector< int > moves, vector< int > expected );

    BoardSize boardSize;

    // Each value defines one move.
    // For example, value 03 means a press square that is in first row and fourth column.
    vector< int > moves;

    vector< int > expectedSquares;
};

#endif // DATACOMMON_H
