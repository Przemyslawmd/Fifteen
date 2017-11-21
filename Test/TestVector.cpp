
#include "TestVector.h"

TestVector::TestVector( BoardSize boardSize, vector< int > moves, vector< int > expectedSquares )
{
    this->boardSize = boardSize;
    this->moves = moves;
    this->expectedSquares = expectedSquares;
}
