
#include "TestVectorGraphic.h"

TestGraphic::TestGraphic( BoardSize boardSize, SquareSize squareSize, GraphicMode mode, ImagesState state, QString path )
    : state( state )
{
    this->boardSize = boardSize;
    this->squareSize = squareSize;
    this->mode = mode;
    this->imagesPath = path;
}
