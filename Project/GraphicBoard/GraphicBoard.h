
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

    bool createScaled( QImage&, BoardSize, TileSize_ );
    bool createCropped( QImage&, BoardSize, TileSize_ );
    bool createSquareImage( QImage*, BoardSize, TileSize_ );
    bool restoreImagesFromFile( QDataStream&, BoardSize, TileSize_ );

    vector< QImage* >& getImages();
    TileSize_ imageSize;

    vector< QImage* > images;
};

#endif // GRAPHIC_BOARD__H
