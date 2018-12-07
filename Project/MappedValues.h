
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>
#include <tuple>
#include <array>

using std::map;
using std::tuple;
using std::array;

class Mapped
{
public:

    static const map< TileSize, int > tileSizeValues;
    static const map< FontSize, int > fontSizeValues;
    static const map< BoardSize, int > BoardSizeInt;
    static const map< TileColor, const QString > tileColorStyles;

    static const array< tuple< TileSize, FontSize >, 5 > tileStyles;

    static BoardSize getKeyBoardSizeMap( int value );
};

#endif // MAPPEDVALUES_H

