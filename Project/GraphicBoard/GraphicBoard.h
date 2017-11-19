
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

    GraphicBoard( int boardSize );
    ~GraphicBoard();

    QImage** getImage();

    int boardSize;

    // Prepared images for graphical board
    QImage** image;

    // Create final images for each square
    bool createSquareImage( QImage* picture, int boardSize, SquareSize size );

    // Restore images from a file buffer data, image of one square has 'bytes' bytes
    bool restoreImagesFromFile( uchar* data, SquareSize size , int bytes );

    bool createScaled( QImage& picture, BoardSize, QString& message, SquareSize size );
    bool createCropped( QImage& picture, BoardSize, QString& message, SquareSize size );
};

#endif // GRAPHIC_BOARD__H
