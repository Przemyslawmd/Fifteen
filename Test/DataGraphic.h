
#ifndef DATAGRAPHIC_H
#define DATAGRAPHIC_H

#include "../Project/Types.h"

class DataGraphic
{
public:
    DataGraphic( BoardSize, SquareSize, GraphicMode, QString imagesPath, bool, bool, bool, bool );

    BoardSize boardSize;
    SquareSize squareSize;
    GraphicMode mode;
    QString imagesPath;
    bool isFourToBeLoaded;
    bool isFiveToBeLoaded;
    bool isSixToBeLoaded;
    bool isSevenToBeLoaded;
};

#endif // DATAGRAPHIC_H
