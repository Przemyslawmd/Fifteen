
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"
#include "../MappedValues.h"

using std::pair;
using std::unique_ptr;


ImageProvider::ImageProvider()
{
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::FOUR,  nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::FIVE,  nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::SIX,   nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::SEVEN, nullptr ));
}

/*********************************************************************************/
/*********************************************************************************/

std::vector< unique_ptr< QImage >>& ImageProvider::getImages( BoardSize boardSize )
{
    return images.at( boardSize )->getImages();
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::prepareGraphicBoard( QImage& image, uint tileSize )
{
    for ( auto iter = images.begin(); iter != images.end(); iter++ )
    {
        if (( Options::isImageToBeLoaded( iter->first )) && ( checkImageSize( image, iter->first, tileSize )))
        {
            createTilesForGraphicBoard( iter->first, tileSize, image );
        }
    }
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::isGraphicBoard( BoardSize boardSize )
{
    return images.at( boardSize ) != nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

uint ImageProvider::getTileSize( BoardSize boardSize )
{
    TileSize tileSize = images.at( boardSize )->tileSize;
    return Maps::tileSizeInt.at( tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

uint ImageProvider::getFontSize( BoardSize boardSize )
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

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::createTilesForGraphicBoard( BoardSize boardSize, uint tileSize, QImage& image )
{
    images.at( boardSize ) = std::make_unique< GraphicBoard >();
    images.at( boardSize )->createTilesFromImage( image, boardSize, tileSize, Options::graphicMode );
}

