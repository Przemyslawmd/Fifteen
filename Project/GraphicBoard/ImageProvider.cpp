
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
    for ( auto iter = images.begin(); iter != images.end(); iter++ )
    {
        if (( Options::isImageToBeLoaded( iter->first )) && ( checkImageSize( image, iter->first, squareSize )))
        {
            letGraphicBoardPrepareImages( iter->first, squareSize, image );
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

SquareSize ImageProvider::getImageSquareSize( BoardSize BoardSize )
{
    return images.at( BoardSize )->imageSize;
}

/*********************************************************************************/
/*********************************************************************************/

bool ImageProvider::restoreGraphicBoardFromFile( QDataStream& stream, BoardSize boardSize )
{
    removeBoard( images.at( boardSize ));
    images.at( boardSize ) = new GraphicBoard();

    int squareSizeInt;
    stream >> squareSizeInt;
    SquareSize squareSize = static_cast< SquareSize >( squareSizeInt );

    if ( squareSize != SquareSize::_50  && squareSize != SquareSize::_75   &&
         squareSize != SquareSize::_100 && squareSize != SquareSize::_125  &&
         squareSize != SquareSize::_150 )
    {
        Message::putMessage( MessageCode::READ_BOARD_IMAGES_ERROR );
        return false;
    }

    if ( images.at( boardSize )->restoreImagesFromFile( stream, boardSize, squareSize ))
    {
        imageSquareSize = squareSize;
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

void ImageProvider::letGraphicBoardPrepareImages( BoardSize boardSize, SquareSize squareSize, QImage& image )
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

