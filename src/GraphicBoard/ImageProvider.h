
#ifndef FIFTEEN_IMAGE_PROVIDER_H
#define FIFTEEN_IMAGE_PROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"
#include "../Message.h"

#include <memory>


class ImageProvider
{
public:

    ImageProvider();
    ImageProvider( const ImageProvider& ) = delete;
    ImageProvider operator=( const ImageProvider& ) = delete;

    std::vector< std::unique_ptr< QImage >>& getImages( BoardSize );

    void prepareGraphicBoard( QImage&, TileSize );
    bool isGraphicBoard( BoardSize );
    TileSize getTileSize( BoardSize );
    uint getFontSize( BoardSize );

private:

    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void createTilesForGraphicBoard( BoardSize, TileSize, QImage& );

    std::map< BoardSize, std::unique_ptr< GraphicBoard >> images;
};

#endif

