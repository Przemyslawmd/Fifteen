#include "Images/Image.h"

/*************************************************************************************************************************/
/* CONSTRUCTOR ***********************************************************************************************************/

Image::Image( int size ) : size( size )
{
    image = new QImage*[size * size];
    for (int i = 0; i < (size * size); i++)
        image[i] = 0;    
}

/**************************************************************************************************************************/
/* DESTRUCTOR *************************************************************************************************************/

Image::~Image()
{
    if (image[0] != 0)
    {
        for (int i = 0; i < (size * size); i++)
            delete image[i];
        delete[] image;
    }    
}

/**************************************************************************************************************************/
/* SEND IMAGE *************************************************************************************************************/

QImage** Image::getImage()
{
    return image;
}

/***************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A SCALE MODE *******************************************************************/

void Image::prepareScaledImage( QImage* image, State& state, QString* message, SquareSize squareSize )
{
    int boardSize = state.size * squareSize;

    if (( image->height() < boardSize ) || ( image->width() < boardSize ))
    {
        message->append( "Too low size of graphic for a board " + state.message );
        return;
    }

    if ( createSquareImage( new QImage( image->scaled( boardSize, boardSize )), state.size, squareSize ))
    {
        state.loaded = true;
        message->append( "Graphic was loaded for a board " + state.message );
    }
    else
        message->append( "Failure of loading graphic for a board " + state.message );
}

/****************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A CROP MODE *********************************************************************/

void Image::prepareCroppedImage( QImage* image, State& state, QString* message, SquareSize squareSize )
{
    int boardSize = state.size * squareSize;

    if (( image->height() < boardSize ) || ( image->width() <  boardSize ))
    {
        message->append( "Too low size of graphic for a board " + state.message );
        return;
    }

    if ( createSquareImage( new QImage(image->copy(( image->width() - boardSize )/2, ( image->height() - boardSize )/2, boardSize, boardSize )), state.size, squareSize ))
    {
        state.loaded = true;
        message->append( "Graphic was loaded for a board" + state.message );
    }
    else
        message->append( "Failure of loading graphic for a board " + state.message );
}

/**************************************************************************************************************************/
/* MAKE IMAGE FOR EACH SQUARE *********************************************************************************************/

bool Image::createSquareImage( QImage* imageWhole, int size, SquareSize squareSize )
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
                        image[x]->setPixel( k, l, imageWhole->pixel( k + j, l + i ));
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
/* RESTORE IMAGES FROM FILE BUFFER *******************************************************************/

bool Image::restoreImagesFromFile( uchar* data, SquareSize imageSize )
{
    bufferRestored = std::move( data );

    try
    {
        for ( int i = 0; i < size * size; i++ )
            image[i] = new QImage( bufferRestored + i * 10000, imageSize, imageSize, QImage::Format_RGB32 );
    }
    catch(...)
    {
        return false;
    }
    return true;
}
