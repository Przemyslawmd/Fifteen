
#ifndef FIFTEEN_IMAGE_PROVIDER_H
#define FIFTEEN_IMAGE_PROVIDER_H

#include <memory>

#include "GraphicBoard.h"
#include "../Types.h"
#include "../Message.h"


class ImageProvider
{
public:

    ImageProvider();
    ImageProvider( const ImageProvider& ) = delete;
    ImageProvider( ImageProvider&& ) = delete;
    ImageProvider& operator=( const ImageProvider& ) = delete;
    ImageProvider& operator=( ImageProvider&& ) = delete;

    std::vector< std::unique_ptr<QImage>>& getImages( BoardSize );

    void prepareGraphicBoard( QImage&, uint tileSize );
    bool isGraphicBoard( BoardSize );
    uint getTileSize( BoardSize );
    uint getFontSize( BoardSize );

private:

    bool checkImageSize( QImage&, BoardSize, uint tileSize ) ;

    std::map<BoardSize, std::unique_ptr<GraphicBoard>> images;
};

#endif

