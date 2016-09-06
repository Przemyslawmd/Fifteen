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

void Image::prepareScaledImage( QImage* image, State& state, QString* message )
{
    if (( image->height() < state.resolution ) || ( image->width() < state.resolution ))
    {
        message->append( "Too low size of graphic for a board " + state.message );
        return;
    }

    if ( createSquareImage( new QImage( image->scaled( state.resolution, state.resolution )), state.size ))
    {
        state.loaded = true;
        message->append( "Graphic was loaded for a board " + state.message );
    }
    else
        message->append( "Failure of loading graphic for a board " + state.message );
}

/****************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE CAN BE LOADED FOR A CROP MODE *********************************************************************/

void Image::prepareCroppedImage( QImage* image, State& state, QString* message )
{
    if (( image->height() < state.resolution ) || ( image->width() < state.resolution ))
    {
        message->append( "Too low size of graphic for a board " + state.message );
        return;
    }

    if ( createSquareImage( new QImage(image->copy(( image->width() - state.resolution)/2, ( image->height() - state.resolution )/2, state.resolution, state.resolution )), state.size ))
    {
        state.loaded = true;
        message->append( "Graphic was loaded for a board" + state.message );
    }
    else
        message->append( "Failure of loading graphic for a board " + state.message );
}

/**************************************************************************************************************************/
/* MAKE IMAGE FOR EACH SQUARE *********************************************************************************************/

bool Image::createSquareImage( QImage* imageWhole, int size )
{
    // Set white (empty) square
    image[0] = new QImage( SQUARE_SIZE, SQUARE_SIZE, QImage::Format_RGB32 );
    for (int i = 0; i < SQUARE_SIZE; i++)
    {
        for (int j = 0; j < SQUARE_SIZE; j++)
            image[0]->setPixel( i, j, qRgb( 255, 255, 255 ));
    }

    int x = 0;

    for ( int i = 0; i < size * SQUARE_SIZE; i += SQUARE_SIZE )
    {
        for ( int j = 0; j < size * SQUARE_SIZE; j += SQUARE_SIZE )
        {
            if (( i == size * SQUARE_SIZE - SQUARE_SIZE ) && ( j == size * SQUARE_SIZE - SQUARE_SIZE ))
                return true;

            try
            {
                image[++x] = new QImage( SQUARE_SIZE, SQUARE_SIZE, QImage::Format_RGB32 );

                for ( int k = 0; k < SQUARE_SIZE; k++ )
                {
                    for ( int l = 0; l < SQUARE_SIZE; l++ )
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

bool Image::restoreImagesFromFile( uchar* data )
{
    bufferRestored = std::move( data );

    try
    {
        for ( int i = 0; i < size * size; i++ )
            image[i] = new QImage( bufferRestored + i * 10000, SQUARE_SIZE, SQUARE_SIZE, QImage::Format_RGB32 );
    }
    catch(...)
    {
        return false;
    }
    return true;
}
