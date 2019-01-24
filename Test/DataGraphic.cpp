
#include "DataGraphic.h"
#include "../Project/MappedValues.h"

DataGraphic::DataGraphic( BoardSize boardSize, TileSize tileSize, GraphicMode mode, QString path,
                          bool four, bool five, bool six, bool seven )
{
    this->size = boardSize;
    this->tileSize = tileSize;
    this->mode = mode;
    imagesPath = path;
    isFourToBeLoaded = four;
    isFiveToBeLoaded = five;
    isSixToBeLoaded = six;
    isSevenToBeLoaded = seven;
}

