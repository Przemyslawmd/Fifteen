
#ifndef FIFTEEN_CONTROLLER_H
#define FIFTEEN_CONTROLLER_H

#include "GraphicBoard/ImageProvider.h"
#include "Types.h"

#include <QImage>

#include <memory>
#include <vector>


class Controller
{
public:

    Controller();
    Controller( const Controller& ) = delete;
    Controller operator=( const Controller& ) = delete;

    bool loadGraphic( QImage& );
    void removeGraphic();
    bool isGraphic( BoardSize );

    TileSize getTileSize( BoardSize );
    std::vector< std::unique_ptr< QImage >>& getImages( BoardSize );

private:

    std::unique_ptr< ImageProvider > imageProvider;
};

#endif

