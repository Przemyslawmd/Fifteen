
#include "DataGraphic.h"
#include "../Project/MappedValues.h"

DataGraphic::DataGraphic( BoardSize boardSize, TileSize tileSize, GraphicMode mode, QString path,
                          bool four, bool five, bool six, bool seven )
{
    this->boardSize = boardSize;
    this->boardSizeInt = Mapped::BoardSizeInt.at( boardSize );
    this->squareSize = tileSize;
    this->mode = mode;
    imagesPath = path;
    isFourToBeLoaded = four;
    isFiveToBeLoaded = five;
    isSixToBeLoaded = six;
    isSevenToBeLoaded = seven;
}

