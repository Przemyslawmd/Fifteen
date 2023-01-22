
#ifndef FIFTEEN_CONTROLLER_H
#define FIFTEEN_CONTROLLER_H

#include "GraphicBoard/ImageProvider.h"

#include <QImage>

#include <memory>


class Controller
{
public:

    Controller();
    Controller( const Controller& ) = delete;
    Controller operator=( const Controller& ) = delete;

    bool loadGraphic( QImage& );
    void removeGraphic();

private:

    std::unique_ptr< ImageProvider > imageProvider;
};

#endif
