
#ifndef TESTVECTORGRAPHIC_H
#define TESTVECTORGRAPHIC_H

#include "../Project/Types.h"

class TestGraphic
{
public:
    TestGraphic( BoardSize, SquareSize, GraphicMode, QString imagesPath, bool, bool, bool, bool );

    BoardSize boardSize;
    SquareSize squareSize;
    GraphicMode mode;
    QString imagesPath;
    bool isFourToBeLoaded;
    bool isFiveToBeLoaded;
    bool isSixToBeLoaded;
    bool isSevenToBeLoaded;
};

#endif // TESTVECTORGRAPHIC_H
