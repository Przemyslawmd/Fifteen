
#include "Data.h"

void Data::DataInit()
{
    if ( isInit )
    {
        return;
    }

    dataGraphic.push_back( DataGraphic
    {
                                BoardSize::FIVE, TileSize::_50, GraphicMode::SCALED,
                                "Scalled_5_50/", false, true, false, false
    });

    dataGraphic.push_back( DataGraphic
    {

                                BoardSize::SIX, TileSize::_75, GraphicMode::CROPPED,
                                "Cropped_6_75/", false, false, true, false
    });

    dataCommon.push_back( DataCommon
    {
                                BoardSize::FOUR,
                                { 13, 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 },
                                { 1, 2, 3, 4, 5, 6, 7, 8, 0, 9, 10, 15, 13, 14, 12, 11 }
    });

    dataCommon.push_back( DataCommon
    {
                                BoardSize::FIVE,
                                { 20, 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 },
                                { 6, 1, 2, 4, 5, 7, 12, 3, 8, 9, 11, 17, 13, 14, 10, 21, 16, 18, 19, 15, 22, 0, 23, 24, 20 }
    });


    isInit = true;
}


DataGraphic& Data::getTestGraphic( int testNumber )
{
    return dataGraphic.at( testNumber );
}


DataCommon& Data::getTestVector( int testNumber )
{
    return dataCommon.at( testNumber );
}


vector< DataCommon > Data::dataCommon;
vector< DataGraphic > Data::dataGraphic;
bool Data::isInit = false;

