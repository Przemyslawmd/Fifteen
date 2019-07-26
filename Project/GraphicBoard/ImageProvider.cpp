
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"
#include "../MappedValues.h"


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

vector< QImage* >& ImageProvider::getImages( BoardSize boardSize )
{
    return images.at( boardSize )->getImages();
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::prepareGraphicBoard( QImage& image, TileSize tileSize )
{
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createTilesFromScaledImage :
                                                                         &GraphicBoard::createTilesFromCroppedImage;
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

Result ImageProvider::restoreGraphicBoardFromFile( QDataStream& stream, BoardSize boardSize )
{
    int tileSizeInt;
    stream >> tileSizeInt;

    if ( tileSizeInt != 50   && tileSizeInt != 75   && tileSizeInt != 100 &&
         tileSizeInt != 125  && tileSizeInt != 150 )
    {
        return Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR;
    }

    TileSize tileSize = Mapped::getTileSizeByInt( tileSizeInt );
    removeBoard( images.at( boardSize ));
    images.at( boardSize ) = new GraphicBoard();

    if ( images.at( boardSize )->restoreImagesFromFile( stream, boardSize, tileSize ) == false )
    {
        removeBoard( images.at( boardSize ));
        return Result::READ_BOARD_IMAGES_DATA_ERROR;
    }

    return Result::OK;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

ImageProvider::ImageProvider()
{
    images.insert( std::pair< BoardSize, GraphicBoard* >( BoardSize::FOUR,  nullptr ));
    images.insert( std::pair< BoardSize, GraphicBoard* >( BoardSize::FIVE,  nullptr ));
    images.insert( std::pair< BoardSize, GraphicBoard* >( BoardSize::SIX,   nullptr ));
    images.insert( std::pair< BoardSize, GraphicBoard* >( BoardSize::SEVEN, nullptr ));
}

/*********************************************************************************/
/*********************************************************************************/

ImageProvider::~ImageProvider()
{
    removeBoard( images.at( BoardSize::FOUR ));
    removeBoard( images.at( BoardSize::FIVE ));
    removeBoard( images.at( BoardSize::SIX ));
    removeBoard( images.at( BoardSize::SEVEN ));
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::checkImageSize( QImage& picture, BoardSize boardSize, TileSize imageSize )
{
    uint tileSizeInt = Mapped::tileSizeInt.at( imageSize );
    uint boardSizeInt = Mapped::boardSizeInt.at( boardSize );
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
    images.at( boardSize ) = new GraphicBoard();
    ( images.at( boardSize )->*createImage )( image, boardSize, tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::removeBoard( GraphicBoard*& board )
{
    delete board;
    board = nullptr;
}

/*********************************************************************************/
/*********************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

