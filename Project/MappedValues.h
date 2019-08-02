
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>

using std::map;

class Mapped
{
public:

    static const map< TileSize, uint > tileSizeInt;
    static const map< FontSize, uint > fontSizeInt;
    static const map< BoardSize, uint > boardSizeInt;
    static const map< TileColor, const QString > tileColorStyle;
    static const map< int, TileSize > sliderTileSize;
    static const map< TileSize, FontSize > tileSizeFontSize;

    static BoardSize getBoardSizeByInt( uint value );
    static TileSize getTileSizeByInt( uint value );
    static int getSliderByTileSize( TileSize value );

private:

    template< typename T, typename U > static T getMapKeyByValue( map< T, U >, U  value );
};

#endif // MAPPEDVALUES_H

