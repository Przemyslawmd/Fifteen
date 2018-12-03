
#ifndef MAPPEDVALUES_H
#define MAPPEDVALUES_H

#include "Types.h"
#include <map>

class MappedValues
{
public:

    static const std::map< TileSize_, int > tileSizeValues;
    static const std::map< FontSize_, int > fontSizeValues;
};

#endif // MAPPEDVALUES_H

