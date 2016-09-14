#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"

class Options
{
public:

    static Size getBoardSize();
    static void setBoardSize( Size );

    static SquareSize getSquareSize();
    static void setSquareSize( int );

    static bool checkNumeric();
    static void setNumeric( bool );

    static bool checkScaled();
    static void setScaled( bool );

    static Color getColor();
    static void setColor( Color );

private:
    Options();

    static Size boardSize;
    static SquareSize squareSize;
    static bool isNumeric;
    static bool isScaled;
    static Color color;
};

#endif // OPTIONS_H
