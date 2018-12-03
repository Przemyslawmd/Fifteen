
#include "MappedValues.h"

const std::map< TileSize, int > MappedValues::tileSizeValues
{
    { TileSize::_50,  50 },
    { TileSize::_75,  75 },
    { TileSize::_100, 100 },
    { TileSize::_125, 125 },
    { TileSize::_150, 150 }
};


const std::map< FontSize, int > MappedValues::fontSizeValues
{
    { FontSize::_20, 20 },
    { FontSize::_25, 25 },
    { FontSize::_30, 30 },
    { FontSize::_35, 35 },
    { FontSize::_40, 40 }
};

