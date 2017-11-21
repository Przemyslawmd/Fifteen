
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"

class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    QImage** getImage( BoardSize );
    void prepareBoardImage( QImage&, SquareSize );
    void restoreImageBoardFromFile( uchar* data, BoardSize, SquareSize, int byteCount );
    bool isImage( BoardSize );
    SquareSize getImageSquareSize();

private:

    ImageProvider();
    ~ImageProvider();

    bool ( GraphicBoard::*createImage )( QImage&, BoardSize, SquareSize );
    bool checkImageSize( QImage&, BoardSize, SquareSize ) ;

    GraphicBoard* boardFour;
    GraphicBoard* boardFive;
    GraphicBoard* boardSix;
    GraphicBoard* boardSeven;

    SquareSize imageSquareSize;

    GraphicBoard* selectBoard( BoardSize );
    GraphicBoard** selectBoardPointer( BoardSize );

    void removeBoard( GraphicBoard** );

    static ImageProvider* instance;
};

#endif // IMAGEPROVIDER_H
