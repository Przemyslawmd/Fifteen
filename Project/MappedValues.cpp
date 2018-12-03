
#include "MappedValues.h"

const std::map< TileSize_, int > MappedValues::tileSizeValues
{
    { TileSize_::_50,  50 },
    { TileSize_::_75,  75 },
    { TileSize_::_100, 100 },
    { TileSize_::_125, 125 },
    { TileSize_::_150, 150 }
};


const std::map< FontSize_, int > MappedValues::fontSizeValues
{
    { FontSize_::_20, 20 },
    { FontSize_::_35, 25 },
    { FontSize_::_30, 30 },
    { FontSize_::_35, 35 },
    { FontSize_::_40, 40 }
};

