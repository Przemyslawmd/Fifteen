
#ifndef TESTDATA_H
#define TESTDATA_H

#include <vector>

using std::vector;

class TestVector
{

public:

    TestVector( int boardSize, vector< int > moves, vector< int > expected );

    int boardSize;

    // Each value defines one move.
    // For example, value 03 means a press square that is in first row and fourth column.
    vector< int > moves;

    vector< int > expectedSquares;
};

#endif // TESTDATA_H
