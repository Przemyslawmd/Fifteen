#ifndef GRAPHIC_BOARD__H
#define GRAPHIC_BOARD__H

#include <QImage>
#include <GraphicBoard/ImageLoad.h>

/*
 * This class is responsible for maintain and preparing
 * images for a graphic board, each level requires one instance of this class
 * ImageProvider is the only class which is allowed to use this class directly
 */

class GraphicBoard
{

private:

    friend class ImageProvider;

    GraphicBoard( int level );
    ~GraphicBoard();

    QImage** getImage();

    int level;
    QImage** image;
    uchar* bufferRestored;

    bool createSquareImage( QImage*, int, SquareSize );
    bool restoreImagesFromFile( uchar*, SquareSize, int );

    void prepareScaledImage( QImage&, State&, QString&, SquareSize );
    void prepareCroppedImage( QImage&, State&, QString&, SquareSize );
};

#endif // GRAPHIC_BOARD__H
