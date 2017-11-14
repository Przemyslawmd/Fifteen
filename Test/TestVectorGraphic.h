
#ifndef TESTVECTORGRAPHIC_H
#define TESTVECTORGRAPHIC_H

#include "../Project/Types.h"
#include "../Project/GraphicBoard/ImageLoad.h"

class TestGraphic
{
public:
    TestGraphic( BoardSize, SquareSize, GraphicMode, ImagesState, QString imagesPath );

    BoardSize boardSize;
    SquareSize squareSize;
    GraphicMode mode;
    ImagesState state;
    QString imagesPath;
};

#endif // TESTVECTORGRAPHIC_H
