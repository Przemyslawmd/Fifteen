
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include "SquareStyle.h"
#include <QString>
#include <QColor>
#include <memory>

using std::unique_ptr;

class Options
{
public:

    static TileSize getSquareSize();
    static FontSize getSquareSizeFont();

    static BoardMode getBoardMode();
    static void setBoardMode( BoardMode mode );

    static GraphicMode getGraphicMode();

    static const QString& getStyle();
    static const QString& getEmptyStyle();

    static bool isImageToBeLoaded( BoardSize size );

    static unique_ptr< NumberOnImage > isNumberOnImage();
    static bool isUndoEnabled();

    static unique_ptr< OptionsData > sendData();
    static void receiveData( unique_ptr< OptionsData > messageData );

private:

    static BoardMode boardMode;
    static GraphicMode graphicMode;

    static int currentTileIndex;
    static Color currentColor;

    static bool imagesToBeLoaded[4];

    static NumberColor numberColor;
    static bool undoEnabled;
};

#endif // OPTIONS_H

