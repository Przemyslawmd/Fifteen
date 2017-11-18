#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "ImageLoad.h"
#include "GraphicBoard.h"
#include "../Types.h"
#include "../Options.h"

class ImageProvider
{
public:

    static ImageProvider* getInstance();
    static void deleteInstance();

    QImage** getImage( int );
    void prepareBoardImage( QImage&, QString&, ImagesState&, SquareSize );
    bool restoreImageBoardFromFile( uchar*, int, SquareSize, int );
    bool isImage( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    bool ( GraphicBoard::*createImage )( QImage& picture, State& state, QString& message, SquareSize size );
    bool checkImageSize( QImage&, State&, SquareSize, QString& ) ;

    enum Index { four = 0, five, six, seven, countImages };

    bool isImageFour;
    bool isImageFive;
    bool isImageSix;
    bool isImageSeven;

    GraphicBoard** images;
    static ImageProvider* instance;
};

#endif // IMAGEPROVIDER_H
