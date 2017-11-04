
#ifndef TESTDATA_H
#define TESTDATA_H

#include <vector>

using std::vector;

class TestVector
{

public:

    TestVector( vector< int >, vector< int > );

    // Each value defines one move.
    // For example, value 23 means a press square that is in second row and third column.
    vector< int > moves;

    vector< int > expectedSquares;
};

#endif // TESTDATA_H
