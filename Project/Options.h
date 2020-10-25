
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>
#include <QColor>
#include <map>
#include <memory>

using std::unique_ptr;
using std::map;

class Options
{
public:

    static BoardMode boardMode;
    static GraphicMode graphicMode;

    static TileColor getTileColor();
    static TileSize getTileSize();

    static bool isImageToBeLoaded( BoardSize size );

    static NumberColor getNumberOnImageColor();
    static bool isUndoEnabled();

    static unique_ptr< OptionsData > readOptions();
    static void saveOptions( unique_ptr< OptionsData > messageData );

private:

    static TileSize tileSize;
    static TileColor tileColor;
    static NumberColor numberColor;
    static bool undoEnabled;
    static map< BoardSize, bool > imagesToLoad;
};

#endif

