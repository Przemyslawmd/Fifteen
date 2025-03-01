
#ifndef FIFTEEN_IMAGE_PROVIDER_H
#define FIFTEEN_IMAGE_PROVIDER_H

#include <memory>

#include "GraphicBoard.h"
#include "Types.h"
#include "Message.h"


class ImageProvider
{
public:

    ImageProvider();
    ImageProvider( const ImageProvider& ) = delete;
    ImageProvider( ImageProvider&& ) = delete;
    ImageProvider& operator=( const ImageProvider& ) = delete;
    ImageProvider& operator=( ImageProvider&& ) = delete;

    const std::vector<QImage>& getImages( BoardSize ) const;

    void prepareGraphicBoard( QImage&, size_t tileSize );
    bool isGraphicBoard( BoardSize ) const;
    size_t getTileSize( BoardSize ) const;
    size_t getFontSize( BoardSize ) const;

private:

    bool checkImageSize( QImage&, BoardSize, size_t tileSize ) const;

    std::map<BoardSize, std::unique_ptr<GraphicBoard>> images;
};

#endif

