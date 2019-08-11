
#include "Data.h"
#include "Defines.h"


DataGraphic& Data::getTestGraphic( int testNumber )
{
    return dataGraphic.at( testNumber );
}

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

