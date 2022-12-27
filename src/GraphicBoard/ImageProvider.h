
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"
#include "../Message.h"


class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    std::vector< std::unique_ptr< QImage >>& getImages( BoardSize );

    void prepareGraphicBoard( QImage&, TileSize );
    bool isGraphicBoard( BoardSize );
    TileSize getTileSize( BoardSize );

private:

    ImageProvider();
    ImageProvider( const ImageProvider& ) = delete;
    ImageProvider operator=( const ImageProvider& ) = delete;

    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void createTilesForGraphicBoard( BoardSize, TileSize, QImage& );

    static ImageProvider* instance;
    std::map< BoardSize, std::unique_ptr< GraphicBoard >> images;
};

#endif

