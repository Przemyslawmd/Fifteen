
#include "Data.h"
#include "Defines.h"


DataGraphic& Data::getTestGraphic( int testNumber )
{
    return dataGraphic.at( testNumber );
}


DataCommon& Data::getTestVector( int testNumber )
{
    return dataCommon.at( testNumber );
}


map< int, DataCommon > Data::dataCommon =
{
    { NUMERIC_FOUR, DataCommon
                    {
                        BoardSize::FOUR,
                        { 13, 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 },
                        { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 }
                    }},

    { NUMERIC_FIVE, DataCommon
                    {
                        BoardSize::FIVE,
                        { 20, 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 },
                        { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 }
                    }}
};

map< int, DataGraphic > Data::dataGraphic =
{
    { GRAPH_FIVE_50_SCALED, DataGraphic
                            {
                                BoardSize::FIVE, TileSize::_50, GraphicMode::SCALED,
                                "Scalled_5_50/", false, true, false, false
                            }
    },

    { GRAPH_SIX_75_CROPPED, DataGraphic
                            {
                                BoardSize::SIX, TileSize::_75, GraphicMode::CROPPED,
                                "Cropped_6_75/", false, false, true, false
                            }
    }
};

