
#ifndef DATA_GRAPHIC_H
#define DATA_GRAPHIC_H

#include "../Project/Types.h"

class DataGraphic
{
public:

    DataGraphic( BoardSize, TileSize, GraphicMode, QString imagesPath, bool, bool, bool, bool );

    BoardSize size;
    TileSize tileSize;
    GraphicMode mode;
    QString imagesPath;
    bool isFourToBeLoaded;
    bool isFiveToBeLoaded;
    bool isSixToBeLoaded;
    bool isSevenToBeLoaded;
};

#endif // DATAGRAPHIC_H

