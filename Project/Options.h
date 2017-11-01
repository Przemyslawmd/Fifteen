
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

    static bool isNumeric();
    static void setNumeric( bool );

    static bool isScaled();
    static void setScaled( bool );

    static Color getColor();
    static void setColor( Color );
    static QString& getStyle();

private:

    static BoardSize boardSize;
    static bool numeric;
    static bool scaled;

    static int currentSquare;
    static Color currentColor;
    static Sizes sizes[5];
    static QString styles[3];
};

#endif // OPTIONS_H

