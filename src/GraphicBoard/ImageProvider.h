
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

    const std::vector<QImage>& getImages( BoardSize ) const;

    void prepareGraphicBoard( QImage&, uint tileSize );
    bool isGraphicBoard( BoardSize ) const;
    uint getTileSize( BoardSize ) const;
    uint getFontSize( BoardSize ) const ;

private:

    bool checkImageSize( QImage&, BoardSize, uint tileSize ) ;

    std::map<BoardSize, std::unique_ptr<GraphicBoard>> images;
};

#endif

