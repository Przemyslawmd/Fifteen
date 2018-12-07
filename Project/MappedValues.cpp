
#include "MappedValues.h"

const map< TileSize, int > Mapped::tileSizeValues
{
    { TileSize::_50,  50 },
    { TileSize::_75,  75 },
    { TileSize::_100, 100 },
    { TileSize::_125, 125 },
    { TileSize::_150, 150 }
};


const map< FontSize, int > Mapped::fontSizeValues
{
    { FontSize::_20, 20 },
    { FontSize::_25, 25 },
    { FontSize::_30, 30 },
    { FontSize::_35, 35 },
    { FontSize::_40, 40 }
};


#define BEGIN_STYLE "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1"
#define END_STYLE   "color:white; border:1px solid white"

const map< TileColor, const QString > Mapped::tileColorStyles
{
    { TileColor::BLUE,        BEGIN_STYLE ", stop:0 #000080, stop:1 #0000EE); " END_STYLE },
    { TileColor::GREEN,       BEGIN_STYLE ", stop:0 #004d00, stop:1 #009900); " END_STYLE },
    { TileColor::RED,         BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE },
    { TileColor::EMPTY_STYLE, "background-color:white; " END_STYLE }
};


const map< BoardSize, int > Mapped::BoardSizeInt
{
    { BoardSize::FOUR,  4 },
    { BoardSize::FIVE,  5 },
    { BoardSize::SIX,   6 },
    { BoardSize::SEVEN, 7 },
};


const array< tuple< TileSize, FontSize >, 5 > Mapped::tileStyles
{
    {
        std::make_tuple( TileSize::_50,  FontSize::_20 ),
        std::make_tuple( TileSize::_75,  FontSize::_25 ),
        std::make_tuple( TileSize::_100, FontSize::_30 ),
        std::make_tuple( TileSize::_125, FontSize::_35 ),
        std::make_tuple( TileSize::_150, FontSize::_40 )
    }
};


BoardSize Mapped::getKeyBoardSizeMap( int value )
{
   for ( auto& map : Mapped::BoardSizeInt )
    {
        if ( map.second == value )
        {
            return map.first;
        }
    }
}

