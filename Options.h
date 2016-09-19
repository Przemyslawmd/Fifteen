#ifndef OPTIONS_H
#define OPTIONS_H

#include "Types.h"
#include <QString>

class Options
{
public:

    static Size getBoardSize();
    static void setBoardSize( Size );

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

    static Size boardSize;
    static SquareSize squareSize;
    static bool isNumeric;
    static bool isScaled;
    static Color color;

    static QString styleBlue;// { "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #000080, stop:1 #0000EE); color:white; border:1px solid white;" };
    static QString styleRed; //{ "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #800000, stop:1 #EE0000); color:white; border:1px solid white;"  };
    static QString styleGreen; //{ "background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #004d00, stop:1 #009900); color:white; border:1px solid white;" };
};

#endif // OPTIONS_H
