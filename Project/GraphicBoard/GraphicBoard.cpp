
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
    int tileSizeInt = Mapped::tileSizeInt.at( tileSize );
    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    int boardSizePixel = boardSizeInt * tileSizeInt;
    QImage scaledImage = image.scaled( boardSizePixel, boardSizePixel );
    createTiles( &scaledImage, boardSizeInt, tileSizeInt );
    this->tileSize = tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTilesFromCroppedImage( QImage& image, BoardSize boardSize, TileSize tileSize )
{
    int tileSizeInt = Mapped::tileSizeInt.at( tileSize );
    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    int boardSizePixel = boardSizeInt * tileSizeInt;
    QImage croppedImage = image.copy(( image.width() - boardSizePixel ) / 2, ( image.height() - boardSizePixel ) / 2,
                                       boardSizePixel, boardSizePixel );
    createTiles( &croppedImage, boardSizeInt, tileSizeInt );
    this->tileSize = tileSize;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTiles( QImage* image, int boardSize, int tileSize )
{
    QImage* tileImage;
    int pictureSize = boardSize * tileSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += tileSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += tileSize )
        {
            if (( yPos == pictureSize - tileSize ) && ( xPos == pictureSize - tileSize ))
            {
                break;
            }

            tileImage = new QImage( image->copy( xPos, yPos, tileSize, tileSize ));
            images.push_back( tileImage );
        }
    }

    tileImage = new QImage( tileSize, tileSize, QImage::Format_RGB32 );
    tileImage->fill( Qt::GlobalColor::white );
    images.push_back( tileImage );
    Message::putMessage( Result::GRAPHIC_LOAD_OK, boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::restoreImagesFromFile( QDataStream& stream, BoardSize boardSize, TileSize tileSize )
{
    int bytesForSquare;
    stream >> bytesForSquare;

    int boardSizeInt = Mapped::boardSizeInt.at( boardSize );
    uchar* buffer = new uchar[bytesForSquare * boardSizeInt * boardSizeInt];
    QImage* image;
    int tileSizeInt = Mapped::tileSizeInt.at( tileSize );

    for ( int i = 0; i < ( boardSizeInt  * boardSizeInt ); i++ )
    {
        if ( stream.readRawData( (char*) ( buffer + i * bytesForSquare ), bytesForSquare ) == -1 )
        {
            return false;
        }
        image = new QImage( buffer + i * bytesForSquare, tileSizeInt, tileSizeInt, QImage::Format_RGB32 );
        images.push_back( image );
    }

    this->tileSize = tileSize;
    return true;
}

