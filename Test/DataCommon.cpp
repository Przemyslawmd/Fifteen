
#include "DataCommon.h"

DataCommon::DataCommon( BoardSize boardSize, vector< int > moves, vector< int > expectedSquares )
{
    this->boardSize = boardSize;
    this->moves = moves;
    this->expectedSquares = expectedSquares;
}

