
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>

class Mapped
{
public:

    static const std::map< TileSize, int > tileSizeValues;
    static const std::map< FontSize, int > fontSizeValues;
    static const std::map< Color, const QString > styles;
};

#endif // MAPPEDVALUES_H

