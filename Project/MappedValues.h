
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>

using std::map;

class Mapped
{
public:

    static const map< TileSize, int > tileSizeInt;
    static const map< FontSize, int > fontSizeInt;
    static const map< BoardSize, int > boardSizeInt;
    static const map< TileColor, const QString > tileColorStyle;
    static const map< int, TileSize > sliderTileSize;
    static const map< TileSize, FontSize > tileSizeFontSize;

    static BoardSize getBoardSizeByInt( int value );
    static int getTileSizeByInt( TileSize value );

private:

    template< typename T, typename U > static T getMapKeyByValue( map< T, U >, U  value );
};

#endif // MAPPEDVALUES_H

