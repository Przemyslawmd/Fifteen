
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"


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

void ImageProvider::prepareGraphicBoard( QImage& image, SquareSize squareSize )
{
    imageSquareSize = squareSize;
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createScaled :
                                                                         &GraphicBoard::createCropped;
    map< BoardSize, GraphicBoard* >::iterator iter;

    for ( iter = images.begin(); iter != images.end(); iter++ )
    {
        if (( Options::isImageToBeLoaded( iter->first )) && ( checkImageSize( image, iter->first, squareSize )))
        {
            tryPrepareGraphicBoard( iter->first, squareSize, image );
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

SquareSize ImageProvider::getImageSquareSize()
{
    return imageSquareSize;
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::restoreGraphicBoardFromFile( unique_ptr< QDataStream > stream, BoardSize boardSize )
{
    removeBoard( images.at( boardSize ));
    images.at( boardSize ) = new GraphicBoard();

    int imageSize;
    *stream >> imageSize;

    if ( imageSize != static_cast< int >( SquareSize::_50 )  && imageSize != static_cast< int >( SquareSize::_75 )  &&
         imageSize != static_cast< int >( SquareSize::_100 ) && imageSize != static_cast< int >( SquareSize::_125 ) &&
         imageSize != static_cast< int >( SquareSize::_150 ))
    {
        Message::putMessage( MessageCode::READ_BOARD_IMAGES_ERROR );
        return false;
    }

    if ( images.at( boardSize )->restoreImagesFromFile( move( stream ), boardSize, static_cast< SquareSize >( imageSize )))
    {
        imageSquareSize = static_cast< SquareSize >( imageSize );
    }
    else
    {
        removeBoard( images.at( boardSize ));
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

bool ImageProvider::checkImageSize( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    if (( picture.height() < boardSize * squareSize ) || ( picture.width() < boardSize * squareSize ))
    {
        Message::putMessage( MessageCode::GRAPHIC_TOO_LOW_SIZE, boardSize );
        return false;
    }

    return true;
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::tryPrepareGraphicBoard( BoardSize boardSize, SquareSize squareSize, QImage& image )
{
    images.at( boardSize ) = new GraphicBoard();

    if (( images.at( boardSize )->*createImage )( image, boardSize, squareSize ) == false )
    {
        removeBoard( images.at( boardSize ));
    }
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

