
#include "GraphicBoard.h"
#include "../Message.h"

/*************************************************************************************************************************/
/* CONSTRUCTOR ***********************************************************************************************************/

GraphicBoard::GraphicBoard( int boardSize ) : boardSize( boardSize )
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
/* SEND IMAGE *************************************************************************************************************/

QImage** GraphicBoard::getImage()
{
    return image;
}

/***************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A SCALE MODE *******************************************************************/

bool GraphicBoard::createScaled( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizeInPixel = boardSize * squareSize;

    if ( createSquareImage( new QImage( picture.scaled( boardSizeInPixel, boardSizeInPixel )), boardSize, squareSize ))
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
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A CROP MODE *********************************************************************/

bool GraphicBoard::createCropped( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    int boardSizeInPixel = boardSize * squareSize;

    if ( createSquareImage( new QImage( picture.copy(( picture.width() - boardSizeInPixel )/2, ( picture.height() - boardSizeInPixel )/2, boardSizeInPixel, boardSizeInPixel )), boardSize, squareSize ))
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

bool GraphicBoard::createSquareImage( QImage* picture, int size, SquareSize squareSize )
{
    // Prepare an empty square
    image[0] = new QImage( squareSize, squareSize, QImage::Format_RGB32 );
    for (int i = 0; i < squareSize; i++)
    {
        for (int j = 0; j < squareSize; j++)
            image[0]->setPixel( i, j, qRgb( 255, 255, 255 ));
    }

    int x = 0;

    for ( int i = 0; i < size * squareSize; i += squareSize )
    {
        for ( int j = 0; j < size * squareSize; j += squareSize )
        {
            if (( i == size * squareSize - squareSize ) && ( j == size * squareSize - squareSize ))
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
