
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>
#include <tuple>
#include <array>

class Mapped
{
public:

    static const std::map< TileSize, int > tileSizeValues;
    static const std::map< FontSize, int > fontSizeValues;
    static const std::map< TileColor, const QString > tileColorStyles;
    static const std::array< std::tuple< TileSize, FontSize >, 5 > tileStyles;
};

#endif // MAPPEDVALUES_H

