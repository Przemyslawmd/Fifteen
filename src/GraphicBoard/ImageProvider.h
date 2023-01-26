
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

    void prepareGraphicBoard( QImage&, uint tileSize );
    bool isGraphicBoard( BoardSize );
    uint getTileSize( BoardSize );
    uint getFontSize( BoardSize );

private:

    bool checkImageSize( QImage&, BoardSize, uint tileSize ) ;
    void createTilesForGraphicBoard( BoardSize, uint tileSize, QImage& );

    std::map< BoardSize, std::unique_ptr< GraphicBoard >> images;
};

#endif

