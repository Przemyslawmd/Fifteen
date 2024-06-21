
#include "MappedValues.h"

using std::map;

const map<TileSize, size_t> Maps::tileSizeInt
{
    { TileSize::_50,  50 },
    { TileSize::_75,  75 },
    { TileSize::_100, 100 },
    { TileSize::_125, 125 },
    { TileSize::_150, 150 }
};


const map<FontSize, size_t> Maps::fontSizeInt
{
    { FontSize::_20, 20 },
    { FontSize::_25, 25 },
    { FontSize::_30, 30 },
    { FontSize::_35, 35 },
    { FontSize::_40, 40 }
};


#define BEGIN_STYLE "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1"
#define END_STYLE   "color:white; border:1px solid white"

const map<TileColor, const QString> Maps::tileColorStyle
{
    { TileColor::BLUE,        BEGIN_STYLE ", stop:0 #000080, stop:1 #0000EE); " END_STYLE },
    { TileColor::GREEN,       BEGIN_STYLE ", stop:0 #004d00, stop:1 #009900); " END_STYLE },
    { TileColor::RED,         BEGIN_STYLE ", stop:0 #800000, stop:1 #EE0000); " END_STYLE },
    { TileColor::EMPTY,       "background-color:white; " END_STYLE }
};


const map<BoardSize, size_t> Maps::boardSizeInt
{
    { BoardSize::FOUR,  4 },
    { BoardSize::FIVE,  5 },
    { BoardSize::SIX,   6 },
    { BoardSize::SEVEN, 7 },
};


const map<TileSize, FontSize> Maps::tileSizeFontSize
{
    { TileSize::_50,  FontSize::_20 },
    { TileSize::_75,  FontSize::_25 },
    { TileSize::_100, FontSize::_30 },
    { TileSize::_125, FontSize::_35 },
    { TileSize::_150, FontSize::_40 }
};


const map<size_t, TileSize> Maps::sliderTileSize
{
    { 0, TileSize::_50 },
    { 1, TileSize::_75 },
    { 2, TileSize::_100 },
    { 3, TileSize::_125 },
    { 4, TileSize::_150 }
};


BoardSize Maps::getBoardSizeByInt( size_t value )
{
   return getMapKeyByValue( Maps::boardSizeInt, value );
}


TileSize Maps::getTileSizeByInt( size_t value )
{
    return getMapKeyByValue( Maps::tileSizeInt, value );
}


int Maps::getSliderByTileSize( TileSize value )
{
   return getMapKeyByValue( Maps::sliderTileSize, value );
}


int Maps::getFontSizeInt( TileSize tileSize )
{
    FontSize fontSize = Maps::tileSizeFontSize.at( tileSize );
    return Maps::fontSizeInt.at( fontSize );
}


template<typename T, typename U> T Maps::getMapKeyByValue( const map<T, U>& pairs, U value )
{
    for ( auto& pair : pairs )
    {
        if ( pair.second == value )
        {
            return pair.first;
        }
    }
    throw "Exception : no key found in a map for a provided value";
}

