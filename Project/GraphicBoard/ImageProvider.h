
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
    void prepareGraphicBoard( QImage&, TileSize_ );
    bool restoreGraphicBoardFromFile( QDataStream&, BoardSize );
    bool isGraphicBoard( BoardSize );
    TileSize_ getImageSquareSize( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    bool ( GraphicBoard::*createImage )( QImage&, BoardSize, TileSize_ );
    bool checkImageSize( QImage&, BoardSize, TileSize_ ) ;
    void letGraphicBoardPrepareImages( BoardSize, TileSize_, QImage& );
    void removeBoard( GraphicBoard*& );

    static ImageProvider* instance;

    std::map< BoardSize, GraphicBoard* > images;
};

#endif // IMAGEPROVIDER_H

