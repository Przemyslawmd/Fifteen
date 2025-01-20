
#include "GraphicBoard.h"
#include "../Message.h"
#include "../MappedValues.h"


const std::vector<QImage>& GraphicBoard::getImages() const
{
    return images;
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTilesFromImage( QImage& sourceImage, BoardSize boardSize, uint tileSize, GraphicMode graphicMode )
{
    uint boardSizeInt = Maps::boardSizeInt.at( boardSize );
    uint boardSizePixel = boardSizeInt * tileSize;

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

    createTiles( boardImage, boardSizeInt, tileSize );
    this->tileSize = Maps::getTileSizeByInt( tileSize );
    this->fontSize = Maps::tileSizeFontSize.at( this->tileSize );
}

/*********************************************************************************/
/*********************************************************************************/

void GraphicBoard::createTiles( QImage& image, uint boardSize, uint tileSize )
{
    uint pictureSize = boardSize * tileSize;
    images.reserve( boardSize * boardSize );

    for ( uint yPos = 0; yPos < pictureSize; yPos += tileSize )
    {
        for ( uint xPos = 0; xPos < pictureSize; xPos += tileSize )
        {
            if (( yPos == pictureSize - tileSize ) && ( xPos == pictureSize - tileSize ))
            {
                break;
            }
            images.emplace_back( image.copy( xPos, yPos, tileSize, tileSize ));
        }
    }

    images.emplace_back( tileSize, tileSize, QImage::Format_RGB32 );
    images.back().fill( Qt::GlobalColor::white );
    Message::putMessage( Result::GRAPHIC_LOAD_OK, boardSize );
}

