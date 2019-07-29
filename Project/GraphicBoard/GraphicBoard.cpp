
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
    int pictureSize = boardSize * tileSize;

    for ( int yPos = 0; yPos < pictureSize; yPos += tileSize )
    {
        for ( int xPos = 0; xPos < pictureSize; xPos += tileSize )
        {
            if (( yPos == pictureSize - tileSize ) && ( xPos == pictureSize - tileSize ))
            {
                break;
            }

            QImage* tileImage = new QImage( image->copy( xPos, yPos, tileSize, tileSize ));
            images.push_back( tileImage );
        }
    }

    QImage* tileImage = new QImage( tileSize, tileSize, QImage::Format_RGB32 );
    tileImage->fill( Qt::GlobalColor::white );
    images.push_back( tileImage );
    Message::putMessage( Result::GRAPHIC_LOAD_OK, boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool GraphicBoard::restoreImagesFromFile( IODataModel& dataModel )
{
    uint boardSizeInt = Mapped::boardSizeInt.at( dataModel.boardSize );
    int tileSizeInt = Mapped::tileSizeInt.at( dataModel.tileSize );

    for ( uint i = 0; i < ( boardSizeInt  * boardSizeInt ); i++ )
    {
        QImage* image = new QImage( dataModel.imagesData + i * dataModel.tileImageBytes, tileSizeInt, tileSizeInt, QImage::Format_RGB32 );
        images.push_back( image );
    }

    this->tileSize = dataModel.tileSize;
    return true;
}

