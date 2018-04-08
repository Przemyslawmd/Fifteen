
#include "GraphicBoard.h"
#include "../Message.h"


GraphicBoard::GraphicBoard( BoardSize boardSize ) : boardSize( boardSize ) {}

/*********************************************************************************/
/* DESTRUCTOR ********************************************************************/

GraphicBoard::~GraphicBoard()
{
    for ( QImage* image : images )
        delete image;
}

/*********************************************************************************/
/* GET IMAGES ********************************************************************/

vector< QImage* >* GraphicBoard::getImages()
{
    return &images;
}

/*********************************************************************************/
/* CREATE SCALED *****************************************************************/

bool GraphicBoard::createScaled( QImage& image, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizePixel = boardSize * squareSize;
    QImage scaledImage = image.scaled( boardSizePixel, boardSizePixel );
    return createSquareImage( &scaledImage, boardSize, squareSize );
}

/*********************************************************************************/
/* CREATE CROPPED ****************************************************************/

bool GraphicBoard::createCropped( QImage& image, BoardSize boardSize, SquareSize squareSize )
{
    int boardPixels = boardSize * squareSize;
    QImage croppedImage = image.copy(( image.width() - boardPixels ) / 2, ( image.height() - boardPixels ) / 2, boardPixels, boardPixels );
    return createSquareImage( &croppedImage, boardSize, squareSize );
}

/*********************************************************************************/
/* CREATE SQUARE IMAGE ***********************************************************/

bool GraphicBoard::createSquareImage( QImage* picture, BoardSize boardSize, SquareSize squareSize )
{
    QImage* image;
    image = new (std::nothrow) QImage( squareSize, squareSize, QImage::Format_RGB32 );

    if ( image == nullptr )
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
        return false;
    }

    image->fill( Qt::GlobalColor::white );
    images.push_back( image );

    int pictureSize = boardSize * squareSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += squareSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += squareSize )
        {
            if (( yPos == pictureSize - squareSize ) && ( xPos == pictureSize - squareSize ))
                break;

            image = new (std::nothrow) QImage( picture->copy( xPos, yPos, squareSize, squareSize ));

            if ( image == nullptr )
            {
                Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
                return false;
            }
            images.push_back( image );
        }
    }

    Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSize );
    return true;
}

/*********************************************************************************/
/* RESTORE IMAGES FROM FILE ******************************************************/

bool GraphicBoard::restoreImagesFromFile( unique_ptr< QDataStream > stream, SquareSize squareSize )
{
    int bytesForSquare;
    *stream >> bytesForSquare;
    uchar* buffer = new uchar[bytesForSquare * boardSize * boardSize];
    QImage* image;

    for ( int i = 0; i < ( boardSize  * boardSize ); i++ )
    {
        stream->readRawData( (char*) ( buffer + i * bytesForSquare ), bytesForSquare );
        image = new (std::nothrow) QImage( buffer + i * bytesForSquare, squareSize, squareSize, QImage::Format_RGB32 );

        if ( image == nullptr )
        {
            delete buffer;
            return false;
        }
        images.push_back( image );
    }
    return true;
}
