
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
    void prepareGraphicBoard( QImage&, TileSize );
    bool restoreGraphicBoardFromFile( QDataStream&, BoardSize );
    bool isGraphicBoard( BoardSize );
    TileSize getImageSquareSize( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    void ( GraphicBoard::*createImage )( QImage&, BoardSize, TileSize );
    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void letGraphicBoardPrepareImages( BoardSize, TileSize, QImage& );
    void removeBoard( GraphicBoard*& );

    static ImageProvider* instance;

    std::map< BoardSize, GraphicBoard* > images;
};

#endif // IMAGEPROVIDER_H

