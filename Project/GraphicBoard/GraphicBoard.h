
#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include "../FileBoard/IODataModel.h"
#include "../Types.h"
#include <QImage>
#include <vector>

using std::vector;
using std::unique_ptr;

class GraphicBoard
{
private:

    friend class ImageProvider;

    GraphicBoard() {}

    void createTilesFromImage( QImage&, BoardSize, TileSize, GraphicMode );
    void createTiles( QImage*, uint boardSize, uint tileSize );
    bool restoreImagesFromFile( IODataModel& );
    vector< unique_ptr< QImage >>& getImages();

    TileSize tileSize;
    vector< unique_ptr< QImage >> images;
};

#endif

