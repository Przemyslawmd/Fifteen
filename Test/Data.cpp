
#include "Data.h"

void Data::DataInit()
{
    if ( isInit )
        return;

    testDataGraphic.push_back( TestGraphic{ BoardSize::FIVE, SquareSize::_50, GraphicMode::SCALED, "Scalled_5_50/", false, true, false, false });
    testDataGraphic.push_back( TestGraphic{ BoardSize::SIX, SquareSize::_75, GraphicMode::CROPPED, "Cropped_6_75/", false, false, true, false });

    testData.push_back( TestVector
    {
                            4,
                            { 13, 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 },
                            { 1, 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 15, 13, 14, 12, 11 }
    });

    testData.push_back( TestVector
    {
                            5,
                            { 20, 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 },
                            { 6, 1, 2, 4, 5, 7, 12, 3, 8, 9, 11, 17, 13, 14, 10, 21, 16, 18, 19, 15, 22, 0, 23, 24, 20 }
    });

    isInit = true;
}


TestGraphic& Data::getTestGraphic(int testNumber )
{
    return testDataGraphic.at( testNumber );
}


TestVector& Data::getTestVector(int testNumber )
{
    return testData.at( testNumber );
}


vector< TestVector > Data::testData;
vector< TestGraphic > Data::testDataGraphic;
bool Data::isInit = false;

