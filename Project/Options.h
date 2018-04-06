
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>
#include <QColor>
#include <memory>

using std::unique_ptr;

class Options
{
public:

    static SquareSize getSquareSize();
    static int getSquareSizeIndex();
    static int getSquareSizeFont();

    static BoardMode getBoardMode();
    static void setBoardMode( BoardMode mode );

    static GraphicMode getGraphicMode();

    static Color getColor();
    static QString& getStyle();
    static QString& getEmptyStyle();

    static bool isImageToBeLoaded( BoardSize size );

    static bool isNumberOnImage();
    static bool isUndoEnabled();

    static unique_ptr< OptionsData > sendData();
    static void receiveData( unique_ptr< OptionsData > messageData );

private:

    static BoardMode boardMode;
    static GraphicMode graphicMode;

    static int currentSquare;
    static Color currentColor;
    static Sizes sizes[5];
    static QString styles[4];
    static bool imagesToBeLoaded[4];

    static bool numberOnImage;
    static bool undoEnabled;
};

#endif // OPTIONS_H

