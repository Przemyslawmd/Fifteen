
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

void GraphicBoard::createTilesFromScaledImage( QImage& image, BoardSize boardSize, TileSize tileSize )
{
    int tileSizeInt = Mapped::tileSizeValues.at( tileSize );
    int boardSizeInt = Mapped::BoardSizeInt.at( boardSize );
    int boardSizePixel = boardSizeInt * tileSizeInt;
    QImage scaledImage = image.scaled( boardSizePixel, boardSizePixel );
    createTiles( &scaledImage, boardSize, tileSizeInt );
    this->tileSize = tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTilesFromCroppedImage( QImage& image, BoardSize boardSize, TileSize tileSize )
{
    int tileSizeInt = Mapped::tileSizeValues.at( tileSize );
    int boardSizeInt = Mapped::BoardSizeInt.at( boardSize );
    int boardSizePixel = boardSizeInt * tileSizeInt;
    QImage croppedImage = image.copy(( image.width() - boardSizePixel ) / 2, ( image.height() - boardSizePixel ) / 2,
                                       boardSizePixel, boardSizePixel );
    createTiles( &croppedImage, boardSize, tileSizeInt );
    this->tileSize = tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTiles( QImage* picture, BoardSize boardSize, int tileSize )
{
    QImage* image = new QImage( tileSize, tileSize, QImage::Format_RGB32 );
    image->fill( Qt::GlobalColor::white );
    images.push_back( image );

    int boardSizeInt = Mapped::BoardSizeInt.at( boardSize );
    int pictureSize = boardSizeInt * tileSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += tileSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += tileSize )
        {
            if (( yPos == pictureSize - tileSize ) && ( xPos == pictureSize - tileSize ))
            {
                break;
            }

            image = new QImage( picture->copy( xPos, yPos, tileSize, tileSize ));
            images.push_back( image );
        }
    }

    Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSizeInt );
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::restoreImagesFromFile( QDataStream& stream, BoardSize boardSize, TileSize imageSize_ )
{
    int imageSize = Mapped::tileSizeValues.at( imageSize_ );
    int bytesForSquare;
    stream >> bytesForSquare;

    int boardSizeInt = Mapped::BoardSizeInt.at( boardSize );

    uchar* buffer = new uchar[bytesForSquare * boardSizeInt * boardSizeInt];
    QImage* image;

    for ( int i = 0; i < ( boardSizeInt  * boardSizeInt ); i++ )
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

