
#ifndef FIFTEEN_OPTIONS_H
#define FIFTEEN_OPTIONS_H

#include <map>

#include <QString>

#include "Types.h"


class Options
{
public:

    static GraphicMode graphicMode;

    static const QString& getTileColor();
    static uint getTileSize();
    static uint getFontSize();

    static bool isImageToBeLoaded( BoardSize size );

    static GraphicTileCaption captionOnGraphicTile();

    static OptionsData readOptions();
    static void saveOptions( OptionsData& messageData );

private:

    static FontSize fontSize;
    static TileSize tileSize;
    static TileColor tileColor;
    static GraphicTileCaption tileCaption;
    static std::map<BoardSize, bool> imagesToLoad;
};

#endif

