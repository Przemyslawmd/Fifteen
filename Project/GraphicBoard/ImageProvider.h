#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"

class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    QImage** getImage( int );
    void prepareBoardImage( QImage&, QString&, SquareSize );
    void restoreImageBoardFromFile( uchar*, int, SquareSize, int );
    bool isImage( BoardSize );
    SquareSize getImageSquareSize();

private:

    ImageProvider();
    ~ImageProvider();

    bool ( GraphicBoard::*createImage )( QImage& picture, BoardSize, QString& message, SquareSize size );
    bool checkImageSize( QImage&, BoardSize, SquareSize, QString& ) ;

    enum Index { four = 0, five, six, seven, countImages };

    bool isImageFour;
    bool isImageFive;
    bool isImageSix;
    bool isImageSeven;
    SquareSize imageSquareSize;

    GraphicBoard** images;
    static ImageProvider* instance;
};

#endif // IMAGEPROVIDER_H
