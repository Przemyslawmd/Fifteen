
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

/*
 * This class prepares and stores images for graphic board.
 * Each size of graphic board requires one instance of this class.
 */

class GraphicBoard
{

private:

    friend class ImageProvider;

    GraphicBoard( BoardSize );
    ~GraphicBoard();

    bool createScaled( QImage&, BoardSize, SquareSize );
    bool createCropped( QImage&, BoardSize, SquareSize );
    bool createSquareImage( QImage*, BoardSize, SquareSize );
    bool restoreImagesFromFile( unique_ptr< QDataStream >, SquareSize );

    vector< QImage* >* getImages();

    BoardSize boardSize;
    vector< QImage* > images;
};

#endif // GRAPHIC_BOARD__H
