
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

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

    GraphicBoard() {};

    void createTilesFromScaledImage( QImage&, BoardSize, TileSize );
    void createTilesFromCroppedImage( QImage&, BoardSize, TileSize );
    void createTiles( QImage*, uint boardSize, uint tileSize );
    bool restoreImagesFromFile( IODataModel& );
    vector< unique_ptr< QImage >>& getImages();

    TileSize tileSize;
    vector< std::unique_ptr< QImage >> images;
};

#endif // GRAPHIC_BOARD__H

