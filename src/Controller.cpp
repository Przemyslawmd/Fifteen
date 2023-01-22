
#include "Controller.h"
#include "Options.h"

Controller::Controller() 
{
}

/*********************************************************************************/
/*********************************************************************************/

bool Controller::loadGraphic( QImage& image )
{
    imageProvider = std::make_unique< ImageProvider >();
    imageProvider->prepareGraphicBoard( image, Options::getTileSize() );

    return imageProvider->isGraphicBoard( BoardSize::FOUR ) || imageProvider->isGraphicBoard( BoardSize::FIVE ) ||
           imageProvider->isGraphicBoard( BoardSize::SIX )  || imageProvider->isGraphicBoard( BoardSize::SEVEN );
}

/*********************************************************************************/
/*********************************************************************************/

void Controller::removeGraphic()
{
    imageProvider.reset();
}

/*********************************************************************************/
/*********************************************************************************/

std::vector< std::unique_ptr< QImage >>& Controller::getImages( BoardSize boardSize )
{
    return imageProvider->getImages( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool Controller::isGraphic( BoardSize boardSize )
{
    return imageProvider != nullptr && imageProvider->isGraphicBoard( boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

TileSize Controller::getTileSize( BoardSize boardSize )
{
    return imageProvider->getTileSize( boardSize );
}

