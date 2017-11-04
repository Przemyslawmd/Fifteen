
#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>

class Options
{
public:

    static BoardSize getBoardSize();
    static void setBoardSize( BoardSize );

    static SquareSize getSquareSize();
    static void setSquareSize( int );
    static int getSquareSizeIndex();
    static int getSquareSizeFont();

    static BoardMode getBoardMode();
    static void setBoardMode( BoardMode mode );

    static bool isScaled();
    static void setScaled( bool );

    static Color getColor();
    static void setColor( Color );
    static QString& getStyle();

private:

    static BoardSize boardSize;
    static BoardMode boardMode;
    static bool scaled;

    static int currentSquare;
    static Color currentColor;
    static Sizes sizes[5];
    static QString styles[3];
};

#endif // OPTIONS_H

