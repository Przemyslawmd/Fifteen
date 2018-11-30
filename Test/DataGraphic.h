
#ifndef DATAGRAPHIC_H
#define DATAGRAPHIC_H

#include "../Project/Types.h"

class DataGraphic
{
public:
    DataGraphic( BoardSize, TileSize, GraphicMode, QString imagesPath, bool, bool, bool, bool );

    BoardSize boardSize;
    TileSize squareSize;
    GraphicMode mode;
    QString imagesPath;
    bool isFourToBeLoaded;
    bool isFiveToBeLoaded;
    bool isSixToBeLoaded;
    bool isSevenToBeLoaded;
};

#endif // DATAGRAPHIC_H
