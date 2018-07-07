
#include "DataGraphic.h"

DataGraphic::DataGraphic( BoardSize board, SquareSize square, GraphicMode mode, QString path,
                          bool four, bool five, bool six, bool seven )
{
    this->boardSize = board;
    this->squareSize = square;
    this->mode = mode;
    imagesPath = path;
    isFourToBeLoaded = four;
    isFiveToBeLoaded = five;
    isSixToBeLoaded = six;
    isSevenToBeLoaded = seven;
}

