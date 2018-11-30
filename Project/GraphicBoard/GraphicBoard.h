
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

/*
 * This class prepares and stores images for a graphic board.
 * Each size of graphic board requires one instance of this class.
 */

class GraphicBoard
{

private:

    friend class ImageProvider;

    GraphicBoard();
    ~GraphicBoard();

    bool createScaled( QImage&, BoardSize, TileSize );
    bool createCropped( QImage&, BoardSize, TileSize );
    bool createSquareImage( QImage*, BoardSize, TileSize );
    bool restoreImagesFromFile( QDataStream&, BoardSize, TileSize );

    vector< QImage* >& getImages();
    TileSize imageSize;

    vector< QImage* > images;
};

#endif // GRAPHIC_BOARD__H
