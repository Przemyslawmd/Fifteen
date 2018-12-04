
#include "MappedValues.h"

const std::map< TileSize, int > Mapped::tileSizeValues
{
    { TileSize::_50,  50 },
    { TileSize::_75,  75 },
    { TileSize::_100, 100 },
    { TileSize::_125, 125 },
    { TileSize::_150, 150 }
};


const std::map< FontSize, int > Mapped::fontSizeValues
{
    { FontSize::_20, 20 },
    { FontSize::_25, 25 },
    { FontSize::_30, 30 },
    { FontSize::_35, 35 },
    { FontSize::_40, 40 }
};


#define BEGIN_STYLE "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1"
#define END_STYLE   "color:white; border:1px solid white"

const std::map< Color, const QString > Mapped::styles
{
    { Color::BLUE,        BEGIN_STYLE ", stop:0 #000080, stop:1 #0000EE); " END_STYLE },
    { Color::GREEN,       BEGIN_STYLE ", stop:0 #004d00, stop:1 #009900); " END_STYLE },
    { Color::RED,         BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE },
    { Color::EMPTY_STYLE, "background-color:white; " END_STYLE }
};
