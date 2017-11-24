
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

bool GraphicBoard::createScaled( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizePixel = boardSize * squareSize;
    QImage scaledPicture = picture.scaled( boardSizePixel, boardSizePixel );

    if ( createSquareImage( &scaledPicture, boardSize, squareSize ))
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSize );
        return true;
    }
    else
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
        return false;
    }
}

/****************************************************************************************************************************/
/* CREATE CROPPED ***********************************************************************************************************/

bool GraphicBoard::createCropped( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizePixel = boardSize * squareSize;
    QImage croppedImage = picture.copy(( picture.width() - boardSizePixel ) / 2, ( picture.height() - boardSizePixel ) / 2, boardSizePixel, boardSizePixel );

    if ( createSquareImage( &croppedImage, boardSize, squareSize ))
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_OK, boardSize );
        return true;
    }
    else
    {
        Message::putMessage( MessageCode::GRAPHIC_LOAD_FAILURE, boardSize );
        return false;
    }
}

/**************************************************************************************************************************/
/* CREATE SQUARE IMAGE ****************************************************************************************************/

bool GraphicBoard::createSquareImage( QImage* picture, BoardSize boardSize, SquareSize squareSize )
{
    // Prepare an empty square
    image[0] = new QImage( squareSize, squareSize, QImage::Format_RGB32 );
    image[0]->fill( Qt::GlobalColor::white );

    int x = 0;
    int pictureSize = boardSize * squareSize;

    for ( int i = 0; i < pictureSize; i += squareSize )
    {
        for ( int j = 0; j < pictureSize; j += squareSize )
        {
            if (( i == pictureSize - squareSize ) && ( j == pictureSize - squareSize ))
                return true;

            try
            {
                image[++x] = new QImage( squareSize, squareSize, QImage::Format_RGB32 );

                for ( int k = 0; k < squareSize; k++ )
                {
                    for ( int l = 0; l < squareSize; l++ )
                        image[x]->setPixel( k, l, picture->pixel( k + j, l + i ));
                }
            }
            catch (...)
            {
                return false;
            }
        }
    }
    return true;
}

/*****************************************************************************************************/
/* RESTORE IMAGES FROM FILE **************************************************************************/

bool GraphicBoard::restoreImagesFromFile( uchar* data, SquareSize squareSize, int bytes )
{
    uchar* bufferRestored = std::move( data );

    try
    {
        for ( int i = 0; i < boardSize * boardSize; i++ )
            image[i] = new QImage( bufferRestored + i * bytes, squareSize, squareSize, QImage::Format_RGB32 );
    }
    catch(...)
    {
        return false;
    }
    return true;
}
