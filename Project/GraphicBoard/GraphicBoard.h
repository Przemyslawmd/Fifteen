
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class GraphicBoard
{

private:

    friend class ImageProvider;

    GraphicBoard();
    ~GraphicBoard();

    bool createTilesFromScaledImage( QImage&, BoardSize, TileSize );
    bool createTilesFromCroppedImage( QImage&, BoardSize, TileSize );
    bool createTiles( QImage*, BoardSize, TileSize );
    bool restoreImagesFromFile( QDataStream&, BoardSize, TileSize );

    vector< QImage* >& getImages();
    TileSize tileSize;

    vector< QImage* > images;
};

#endif // GRAPHIC_BOARD__H

