
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"
#include <memory>

using std::unique_ptr;

class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    vector< QImage* >& getImages( BoardSize );
    void prepareGraphicBoard( QImage&, SquareSize );
    bool restoreGraphicBoardFromFile( unique_ptr< QDataStream >, BoardSize );
    bool isGraphicBoard( BoardSize );
    SquareSize getImageSquareSize();

private:

    ImageProvider();
    ~ImageProvider();

    bool ( GraphicBoard::*createImage )( QImage&, BoardSize, SquareSize );
    bool checkImageSize( QImage&, BoardSize, SquareSize ) ;
    void letGraphicBoardPrepareImages( BoardSize, SquareSize, QImage& );
    void removeBoard( GraphicBoard*& );

    static ImageProvider* instance;

    SquareSize imageSquareSize;
    std::map< BoardSize, GraphicBoard* > images;
};

#endif // IMAGEPROVIDER_H

