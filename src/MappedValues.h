
#ifndef FIFTEEN_MAPPED_VALUES_H
#define FIFTEEN_MAPPED_VALUES_H

#include "Types.h"

#include <QString>

#include <map>


class Maps
{
public:

    static const std::map< TileSize, uint > tileSizeInt;
    static const std::map< FontSize, uint > fontSizeInt;
    static const std::map< BoardSize, uint > boardSizeInt;
    static const std::map< TileColor, const QString > tileColorStyle;
    static const std::map< int, TileSize > sliderTileSize;
    static const std::map< TileSize, FontSize > tileSizeFontSize;

    static int getFontSizeInt( TileSize tileSize );
    static BoardSize getBoardSizeByInt( uint value );
    static TileSize getTileSizeByInt( uint value );
    static int getSliderByTileSize( TileSize value );

private:

    template< typename T, typename U > static T getMapKeyByValue( std::map< T, U >, U  value );
};

#endif

