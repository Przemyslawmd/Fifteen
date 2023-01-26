
#include "GraphicBoard.h"
#include "../Message.h"
#include "../MappedValues.h"


std::vector< std::unique_ptr< QImage >>& GraphicBoard::getImages()
{
    return images;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTilesFromImage( QImage& sourceImage, BoardSize boardSize, TileSize tileSize, GraphicMode graphicMode )
{
    uint tileSizeInt = Maps::tileSizeInt.at( tileSize );
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );
    uint boardSizePixel = boardSizeInt * tileSizeInt;

    QImage boardImage;
    if ( graphicMode == GraphicMode::SCALED )
    {
        boardImage = sourceImage.scaled( boardSizePixel, boardSizePixel );
    }
    else
    {
        boardImage = sourceImage.copy(( sourceImage.width() - boardSizePixel ) / 2,
                                      ( sourceImage.height() - boardSizePixel ) / 2,
                                        boardSizePixel,
                                        boardSizePixel );
    }

    createTiles( &boardImage, boardSizeInt, tileSizeInt );
    this->tileSize = tileSize;
    this->fontSize = Maps::tileSizeFontSize.at( tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTiles( QImage* image, uint boardSize, uint tileSize )
{
    uint pictureSize = boardSize * tileSize;

    for ( uint yPos = 0; yPos < pictureSize; yPos += tileSize )
    {
        for ( uint xPos = 0; xPos < pictureSize; xPos += tileSize )
        {
            if (( yPos == pictureSize - tileSize ) && ( xPos == pictureSize - tileSize ))
            {
                break;
            }
            images.push_back( std::make_unique< QImage >( image->copy( xPos, yPos, tileSize, tileSize )));
        }
    }

    QImage tileImage ( tileSize, tileSize, QImage::Format_RGB32 );
    tileImage.fill( Qt::GlobalColor::white );
    images.push_back( std::make_unique< QImage >( tileImage ));
    Message::putMessage( Result::GRAPHIC_LOAD_OK, boardSize );
}

