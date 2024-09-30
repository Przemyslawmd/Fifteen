
#ifndef FIFTEEN_OPTIONS_H
#define FIFTEEN_OPTIONS_H

#include "Types.h"

#include <QString>

#include <map>


class Options
{
public:

    static GraphicMode graphicMode;

    static const QString& getTileColor();
    static uint getTileSize();
    static uint getFontSize();

    static bool isImageToBeLoaded( BoardSize size );

    static NumberColor getNumberOnImageColor();

    static OptionsData readOptions();
    static void saveOptions( OptionsData& messageData );

private:

    static FontSize fontSize;
    static TileSize tileSize;
    static TileColor tileColor;
    static NumberColor numberColor;
    static std::map<BoardSize, bool> imagesToLoad;
};

#endif

