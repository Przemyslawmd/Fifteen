
#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include "../Types.h"
#include <QImage>

/*
 * This class is responsible for maintaining and preparing
 * images for a graphic board. Each level (board size) requires one instance of this class.
 * ImageProvider is the only one class which is allowed to use this class directly
 */

class GraphicBoard
{

private:

    friend class ImageProvider;

    GraphicBoard( BoardSize );
    ~GraphicBoard();

    QImage** getImage();

    BoardSize boardSize;

    // Prepared images for graphical board
    QImage** image;

    // Create final images for each square
    bool createSquareImage( QImage*, BoardSize, SquareSize );

    // Restore images from a file buffer data, image of one square has 'bytes' bytes
    bool restoreImagesFromFile( uchar* buffer, SquareSize, int countOfBytes );

    bool createScaled( QImage&, BoardSize, SquareSize );
    bool createCropped( QImage&, BoardSize, SquareSize );
};

#endif // GRAPHIC_BOARD__H
