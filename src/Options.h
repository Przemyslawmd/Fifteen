
#ifndef FIFTEEN_OPTIONS_H
#define FIFTEEN_OPTIONS_H

#include "Types.h"

#include <QString>

#include <map>
#include <memory>


class Options
{
public:

    static GraphicMode graphicMode;

    static TileColor getTileColor();
    static TileSize getTileSize();

    static bool isImageToBeLoaded( BoardSize size );

    static NumberColor getNumberOnImageColor();

    static std::unique_ptr< OptionsData > readOptions();
    static void saveOptions( std::unique_ptr< OptionsData > messageData );

private:

    static TileSize tileSize;
    static TileColor tileColor;
    static NumberColor numberColor;
    static std::map< BoardSize, bool > imagesToLoad;
};

#endif

