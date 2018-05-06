
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
    removeBoard( images[BoardSize::FOUR]);
    removeBoard( images[BoardSize::FIVE]);
    removeBoard( images[BoardSize::SIX]);
    removeBoard( images[BoardSize::SEVEN]);
}

/*********************************************************************************/
/*********************************************************************************/

void ImageProvider::prepareGraphicBoard( QImage& image, SquareSize squareSize )
{
    imageSquareSize = squareSize;
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createScaled :
                                                                         &GraphicBoard::createCropped;

    if (( Options::isImageToBeLoaded( BoardSize::FOUR )) && ( checkImageSize( image, BoardSize::FOUR, squareSize )))
    {
        tryPrepareGraphicBoard( BoardSize::FOUR, squareSize, image );
    }

    if (( Options::isImageToBeLoaded( BoardSize::FIVE )) && ( checkImageSize( image, BoardSize::FIVE, squareSize )))
    {
        tryPrepareGraphicBoard( BoardSize::FIVE, squareSize, image );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SIX )) && ( checkImageSize( image, BoardSize::SIX, squareSize )))
    {
        tryPrepareGraphicBoard( BoardSize::SIX, squareSize, image );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SEVEN )) && ( checkImageSize( image, BoardSize::SEVEN, squareSize )))
    {
        tryPrepareGraphicBoard( BoardSize::SEVEN, squareSize, image );
    }
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
    images.at( boardSize ) = new GraphicBoard( boardSize );

    if (( images.at( boardSize )->*createImage )( image, boardSize, squareSize ) == false )
    {
        removeBoard( images.at( boardSize ));
    }
}

/*********************************************************************************/
/*********************************************************************************/

vector< QImage* >& ImageProvider::getImages( BoardSize boardSize )
{
    return images.at( boardSize )->getImages();
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::isImage( BoardSize boardSize )
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

bool ImageProvider::restoreImageBoardFromFile( unique_ptr< QDataStream > stream, BoardSize boardSize )
{
    removeBoard( images.at( boardSize ));
    images.at( boardSize ) = new GraphicBoard( boardSize );

    int imageSize;
    *stream >> imageSize;

    if ( imageSize != (int) SquareSize::_50  && imageSize != (int) SquareSize::_75 && imageSize != (int) SquareSize::_100 &&
         imageSize != (int) SquareSize::_125 && imageSize != (int) SquareSize::_150 )
    {
        Message::putMessage( MessageCode::READ_BOARD_IMAGES_ERROR );
        return false;
    }

    if ( images.at( boardSize )->restoreImagesFromFile( std::move( stream ), (SquareSize) imageSize ))
    {
        imageSquareSize = (SquareSize) imageSize;
    }
    else
    {
        removeBoard( images.at( boardSize ));
    }

    return true;
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


