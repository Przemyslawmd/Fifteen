
#ifndef OPTIONS_H
#define OPTIONS_H

#include <map>
#include <memory>
#include <QString>
#include "Types.h"


class Options
{
public:

    static BoardMode boardMode;
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

