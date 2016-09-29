#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>

class Options
{
public:

    static Level getLevel();
    static void setLevel( Level );

    static SquareSize getSquareSize();
    static void setSquareSize( int );
    static int getSquareSizeIndex();

    static int getFontSquareSize();

    static bool checkNumeric();
    static void setNumeric( bool );

    static bool checkScaled();
    static void setScaled( bool );

    static Color getColor();
    static void setColor( Color );
    static QString* getStyle();

private:
    Options();

    static Level level;
    static SquareSize squareSize;
    static bool isNumeric;
    static bool isScaled;
    static Color color;

    static QString styleBlue;
    static QString styleRed;
    static QString styleGreen;
};

#endif // OPTIONS_H
