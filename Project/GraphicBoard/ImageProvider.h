
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"

class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    vector< QImage* >& getImages( BoardSize );
    void prepareGraphicBoard( QImage&, TileSize );
    bool restoreGraphicBoardFromFile( QDataStream&, BoardSize );
    bool isGraphicBoard( BoardSize );
    TileSize getTileSize( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void createTilesForGraphicBoard( BoardSize, TileSize, QImage& );
    void removeBoard( GraphicBoard*& );

    void ( GraphicBoard::*createImage )( QImage&, BoardSize, TileSize );

    static ImageProvider* instance;
    std::map< BoardSize, GraphicBoard* > images;
};

#endif

