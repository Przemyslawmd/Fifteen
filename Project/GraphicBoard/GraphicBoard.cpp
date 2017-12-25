
#include "GraphicBoard.h"
#include "../Message.h"

/*************************************************************************************************************************/
/* CONSTRUCTOR ***********************************************************************************************************/

GraphicBoard::GraphicBoard( BoardSize boardSize ) : boardSize( boardSize )
{
    image = new QImage*[boardSize  * boardSize];
    for ( int i = 0; i < ( boardSize * boardSize ); i++ )
        image[i] = 0;    
}

/**************************************************************************************************************************/
/* DESTRUCTOR *************************************************************************************************************/

GraphicBoard::~GraphicBoard()
{
    if ( image[0] == nullptr )
        return;

    for ( int i = 0; i < ( boardSize * boardSize ); i++ )
        delete image[i];

    delete[] image;
}

/**************************************************************************************************************************/
/* GET IMAGE *************************************************************************************************************/

QImage** GraphicBoard::getImage()
{
    return image;
}

/***************************************************************************************************************************/
/* CREATE SCALED ***********************************************************************************************************/

bool GraphicBoard::createScaled( QImage& image, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizePixel = boardSize * squareSize;
    QImage scaledImage = image.scaled( boardSizePixel, boardSizePixel );
    return createSquareImage( &scaledImage, boardSize, squareSize );
}

/****************************************************************************************************************************/
/* CREATE CROPPED ***********************************************************************************************************/

bool GraphicBoard::createCropped( QImage& image, BoardSize boardSize, SquareSize squareSize )
{
    int boardPixels = boardSize * squareSize;
    QImage croppedImage = image.copy(( image.width() - boardPixels ) / 2, ( image.height() - boardPixels ) / 2, boardPixels, boardPixels );
    return createSquareImage( &croppedImage, boardSize, squareSize );
}

/**************************************************************************************************************************/
/* CREATE SQUARE IMAGE ****************************************************************************************************/

bool GraphicBoard::createSquareImage( QImage* picture, BoardSize boardSize, SquareSize squareSize )
{
    // Prepare an empty square
    image[0] = new (std::nothrow) QImage( squareSize, squareSize, QImage::Format_RGB32 );

    if ( image[0] == nullptr )
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
        return false;
    }

    image[0]->fill( Qt::GlobalColor::white );

    int x = 0;
    int pictureSize = boardSize * squareSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += squareSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += squareSize )
        {
            if (( yPos == pictureSize - squareSize ) && ( xPos == pictureSize - squareSize ))
                break;

            image[++x] = new (std::nothrow) QImage( picture->copy( xPos, yPos, squareSize, squareSize ));

            if ( image[x] == nullptr )
            {
                Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
                return false;
            }
        }
    }

    Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSize );
    return true;
}

/*****************************************************************************************************/
/* RESTORE IMAGES FROM FILE **************************************************************************/

bool GraphicBoard::restoreImagesFromFile( unique_ptr< QDataStream > stream, SquareSize squareSize )
{
    int bytesOfSquare;
    *stream >> bytesOfSquare;

    uchar* buffer = new uchar[bytesOfSquare * boardSize * boardSize];
    for ( int i = 0; i < ( boardSize  * boardSize ); i++ )
        stream->readRawData( (char*) ( buffer + i * bytesOfSquare ), bytesOfSquare );

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        image[i] = new (std::nothrow) QImage( buffer + i * bytesOfSquare, squareSize, squareSize, QImage::Format_RGB32 );

        if ( image[i] == nullptr )
            return false;

    }
    return true;
}
