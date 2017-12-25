
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>
#include <memory>

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

    QImage** getImage();

    BoardSize boardSize;

    // Prepared images for a graphic board
    QImage** image;

    bool createScaled( QImage&, BoardSize, SquareSize );
    bool createCropped( QImage&, BoardSize, SquareSize );
    bool createSquareImage( QImage*, BoardSize, SquareSize );

    bool restoreImagesFromFile( unique_ptr< QDataStream >, SquareSize );
};

#endif // GRAPHIC_BOARD__H
