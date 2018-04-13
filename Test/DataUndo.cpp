#include "DataUndo.h"

DataUndo::DataUndo( BoardSize size, vector< int > moves_1, vector< int > moves_2, vector< int > moves3,
                    int undoSteps1, int undoSteps2, int undoSteps3, vector< int > expectedBoard ) :
                    DataCommon( size, moves_1, expectedBoard )
{
    this->moves_2 = moves_2;
    this->moves_3 = moves_3;
    this->undoSteps_1 = undoSteps1;
    this->undoSteps_2 = undoSteps2;
}
