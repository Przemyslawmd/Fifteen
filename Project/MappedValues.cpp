
#include "MappedValues.h"

const std::map< TileSize, int > MappedValues::tileSizeValues
{
    { TileSize::_50,  50 },
    { TileSize::_75,  75 },
    { TileSize::_100, 100 },
    { TileSize::_125, 125 },
    { TileSize::_150, 150 }
};


const std::map< FontSize_, int > MappedValues::fontSizeValues
{
    { FontSize_::_20, 20 },
    { FontSize_::_35, 25 },
    { FontSize_::_30, 30 },
    { FontSize_::_35, 35 },
    { FontSize_::_40, 40 }
};

