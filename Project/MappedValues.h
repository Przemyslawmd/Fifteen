
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>

using std::map;

class Mapped
{
public:

    static const map< TileSize, int > tileSizeValues;
    static const map< FontSize, int > fontSizeValues;
    static const map< BoardSize, int > BoardSizeInt;
    static const map< TileColor, const QString > tileColorStyles;
    static const map< int, TileSize > sliderTileSizeMap;
    static const map< TileSize, FontSize > mapTileFont;

    static BoardSize getBoardSizeByInt( int value );
    static int getTileSizeByInt( TileSize value );

    template< typename T, typename U > static T getMapKeyByValue( map< T, U >, U  value );
};

#endif // MAPPEDVALUES_H

