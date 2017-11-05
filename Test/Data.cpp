
#include "Data.h"

vector< int > Data::getMoves( int testNumber )
{
    return testData.at( testNumber ).moves;
}


vector< int > Data::getExpectedSquares( int testNumber )
{
    return testData.at( testNumber ).expectedSquares;
}


int Data::getBoardSize( int testNumber )
{
    return testData.at( testNumber ).boardSize;
}


vector< TestVector > Data::testData
{
    { TestVector(
                    4,
                    { 13, 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 },
                    { 1, 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 15, 13, 14, 12, 11 }
                )
    },

    { TestVector(
                    5,
                    { 20, 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 },
                    { 6, 1, 2, 4, 5, 7, 12, 3, 8, 9, 11, 17, 13, 14, 10, 21, 16, 18, 19, 15, 22, 0, 23, 24, 20 }
                )
    },
};
