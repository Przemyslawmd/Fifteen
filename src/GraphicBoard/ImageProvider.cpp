
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"
#include "../MappedValues.h"

using std::pair;
using std::unique_ptr;


ImageProvider& ImageProvider::getInstance()
{
    if ( instance == nullptr )
    {
        instance = new ImageProvider();
    }

    return *instance;
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::deleteInstance()
{
    delete instance;
    instance = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

std::vector< unique_ptr< QImage >>& ImageProvider::getImages( BoardSize boardSize )
{
    return images.at( boardSize )->getImages();
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::prepareGraphicBoard( QImage& image, TileSize tileSize )
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

TileSize ImageProvider::getTileSize( BoardSize boardSize )
{
    return images.at( boardSize )->tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::restoreBoardFromFile( IODataModel& dataModel )
{
    BoardSize boardSize = dataModel.boardSize;
    images.at( boardSize ).reset( new GraphicBoard() );

    if ( images.at( boardSize )->restoreImagesFromFile( dataModel ) == false )
    {
        images.at( boardSize ).reset();
        return false;
    }

    return true;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

ImageProvider::ImageProvider()
{
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::FOUR,  nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::FIVE,  nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::SIX,   nullptr ));
    images.insert( pair< BoardSize, unique_ptr< GraphicBoard >>( BoardSize::SEVEN, nullptr ));
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::checkImageSize( QImage& picture, BoardSize boardSize, TileSize tileSize )
{
    uint tileSizeInt = Maps::tileSizeInt.at( tileSize );
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );
    if (( picture.height() < boardSizeInt * tileSizeInt ) || ( picture.width() < boardSizeInt * tileSizeInt ))
    {
        Message::putMessage( Result::GRAPHIC_TOO_LOW_SIZE, boardSizeInt );
        return false;
    }

    return true;
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::createTilesForGraphicBoard( BoardSize boardSize, TileSize tileSize, QImage& image )
{
    images.at( boardSize ) = std::make_unique< GraphicBoard >();
    images.at( boardSize )->createTilesFromImage( image, boardSize, tileSize, Options::graphicMode );
}

/*********************************************************************************/
/*********************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

