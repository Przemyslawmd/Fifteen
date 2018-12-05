
#include "GraphicBoard.h"
#include "../Message.h"
#include "../MappedValues.h"

GraphicBoard::GraphicBoard() {}

/*********************************************************************************/
/*********************************************************************************/

GraphicBoard::~GraphicBoard()
{
    for ( QImage* image : images )
    {
        delete image;
    }
}

/*********************************************************************************/
/*********************************************************************************/

vector< QImage* >& GraphicBoard::getImages()
{
    return images;
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::createTilesFromScaledImage( QImage& image, BoardSize boardSize, TileSize tileSize )
{
    int tileSizeInt = Mapped::tileSizeValues.at( tileSize );
    int boardSizePixel = boardSize * tileSizeInt;
    QImage scaledImage = image.scaled( boardSizePixel, boardSizePixel );
    return createTiles( &scaledImage, boardSize, tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::createTilesFromCroppedImage( QImage& image, BoardSize boardSize, TileSize squareSize )
{
    int tileSizeInt = Mapped::tileSizeValues.at( squareSize );
    int boardPixels = boardSize * tileSizeInt;
    QImage croppedImage = image.copy(( image.width() - boardPixels ) / 2, ( image.height() - boardPixels ) / 2,
                                       boardPixels, boardPixels );
    return createTiles( &croppedImage, boardSize, squareSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::createTiles( QImage* picture, BoardSize boardSize, TileSize imageSize_ )
{
    int imageSize = Mapped::tileSizeValues.at( imageSize_ );
    QImage* image = new (std::nothrow) QImage( imageSize, imageSize, QImage::Format_RGB32 );

    if ( image == nullptr )
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
        return false;
    }

    image->fill( Qt::GlobalColor::white );
    images.push_back( image );

    int pictureSize = boardSize * imageSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += imageSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += imageSize )
        {
            if (( yPos == pictureSize - imageSize ) && ( xPos == pictureSize - imageSize ))
            {
                break;
            }

            image = new (std::nothrow) QImage( picture->copy( xPos, yPos, imageSize, imageSize ));

            if ( image == nullptr )
            {
                Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
                return false;
            }
            images.push_back( image );
        }
    }

    this->tileSize = imageSize_;
    Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSize );
    return true;
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::restoreImagesFromFile( QDataStream& stream, BoardSize boardSize, TileSize imageSize_ )
{
    int imageSize = Mapped::tileSizeValues.at( imageSize_ );
    int bytesForSquare;
    stream >> bytesForSquare;
    uchar* buffer = new uchar[bytesForSquare * boardSize * boardSize];
    QImage* image;

    for ( int i = 0; i < ( boardSize  * boardSize ); i++ )
    {
        stream.readRawData( (char*) ( buffer + i * bytesForSquare ), bytesForSquare );
        image = new (std::nothrow) QImage( buffer + i * bytesForSquare, imageSize, imageSize, QImage::Format_RGB32 );

        if ( image == nullptr )
        {
            delete buffer;
            return false;
        }
        images.push_back( image );
    }

    this->tileSize = imageSize_;
    return true;
}

