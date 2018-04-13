#ifndef DATAUNDO_H
#define DATAUNDO_H

#include "DataCommon.h"
#include "../Project/Types.h"
#include <vector>

using std::vector;

class DataUndo : public DataCommon
{
public:

    DataUndo( BoardSize, vector< int >, vector< int >, vector< int >, int, int, vector< int > );

private:

    vector< int > moves_2;
    vector< int > moves_3;

    int undoSteps_1;
    int undoSteps_2;
};

#endif // DATAUNDO_H
