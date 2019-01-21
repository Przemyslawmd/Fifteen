
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>
#include <vector>

using std::vector;

class GraphicBoard
{
private:

    friend class ImageProvider;

    GraphicBoard();
    ~GraphicBoard();

    void createTilesFromScaledImage( QImage&, BoardSize, TileSize );
    void createTilesFromCroppedImage( QImage&, BoardSize, TileSize );
    void createTiles( QImage*, int boardSize, int tileSize );
    bool restoreImagesFromFile( QDataStream&, BoardSize, TileSize );

    vector< QImage* >& getImages();
    TileSize tileSize;

    vector< QImage* > images;
};

#endif // GRAPHIC_BOARD__H

