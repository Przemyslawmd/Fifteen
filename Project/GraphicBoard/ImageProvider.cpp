
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
    if ( instance == nullptr )
    {
        return;
    }

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

void ImageProvider::prepareGraphicBoard( QImage& image, TileSize imageSize )
{
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createTilesFromScaledImage :
                                                                         &GraphicBoard::createTilesFromCroppedImage;
    for ( auto iter = images.begin(); iter != images.end(); iter++ )
    {
        if (( Options::isImageToBeLoaded( iter->first )) && ( checkImageSize( image, iter->first, imageSize )))
        {
            letGraphicBoardPrepareImages( iter->first, imageSize, image );
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

bool ImageProvider::restoreGraphicBoardFromFile( QDataStream& stream, BoardSize boardSize )
{
    removeBoard( images.at( boardSize ));
    images.at( boardSize ) = new GraphicBoard();

    int tileSizeInt;
    stream >> tileSizeInt;
    TileSize tileSize = Mapped::getTileSizeByInt( tileSizeInt );

    if ( tileSize != TileSize::_50  && tileSize != TileSize::_75   &&
         tileSize != TileSize::_100 && tileSize != TileSize::_125  &&
         tileSize != TileSize::_150 )
    {
        Message::putMessage( MessageCode::READ_BOARD_IMAGES_TILE_SIZE_ERROR );
        return false;
    }

    if ( images.at( boardSize )->restoreImagesFromFile( stream, boardSize, tileSize ) == false )
    {
        removeBoard( images.at( boardSize ));
        Message::putMessage( MessageCode::READ_BOARD_IMAGES_DATA_ERROR );
        return false;
    }

    return true;
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
    int tileSizeInt = Mapped::tileSizeInt.at( imageSize );
    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    if (( picture.height() < boardSizeInt * tileSizeInt ) || ( picture.width() < boardSizeInt * tileSizeInt ))
    {
        Message::putMessage( MessageCode::GRAPHIC_TOO_LOW_SIZE, boardSizeInt );
        return false;
    }

    return true;
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::letGraphicBoardPrepareImages( BoardSize boardSize, TileSize tileSize, QImage& image )
{
    images.at( boardSize ) = new GraphicBoard();
    ( images.at( boardSize )->*createImage )( image, boardSize, tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::removeBoard( GraphicBoard*& board )
{
    if ( board != nullptr )
    {
        delete board;
        board = nullptr;
    }
}

/*********************************************************************************/
/*********************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

