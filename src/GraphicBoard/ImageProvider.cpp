
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"
#include "../MappedValues.h"


ImageProvider::ImageProvider()
{
    images.emplace( BoardSize::FOUR, nullptr );
    images.emplace( BoardSize::FIVE, nullptr );
    images.emplace( BoardSize::SIX, nullptr );
    images.emplace( BoardSize::SEVEN, nullptr );
}

/*********************************************************************************/
/*********************************************************************************/

const std::vector<QImage>& ImageProvider::getImages( BoardSize boardSize ) const
{
    return images.at( boardSize )->getImages();
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::prepareGraphicBoard( QImage& image, uint tileSize )
{
    for ( const auto& [boardSize, _] : images )
    {
        if (( Options::isImageToBeLoaded( boardSize )) && ( checkImageSize( image, boardSize, tileSize )))
        {
            images.at( boardSize ) = std::make_unique<GraphicBoard>();
            images.at( boardSize )->createTilesFromImage( image, boardSize, tileSize, Options::graphicMode );
        }
    }
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::isGraphicBoard( BoardSize boardSize ) const
{
    return images.at( boardSize ) != nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

uint ImageProvider::getTileSize( BoardSize boardSize ) const
{
    TileSize tileSize = images.at( boardSize )->tileSize;
    return Maps::tileSizeInt.at( tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

uint ImageProvider::getFontSize( BoardSize boardSize ) const
{
    FontSize fontSize = images.at( boardSize )->fontSize;
    return Maps::fontSizeInt.at( fontSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::checkImageSize( QImage& picture, BoardSize boardSize, uint tileSize )
{
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );
    if (( picture.height() < boardSizeInt * tileSize ) || ( picture.width() < boardSizeInt * tileSize ))
    {
        Message::putMessage( Result::GRAPHIC_TOO_LOW_SIZE, boardSizeInt );
        return false;
    }
    return true;
}

