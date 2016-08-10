#include "Image_.h"


/*************************************************************************************************************************/
/* CONSTRUCTOR ***********************************************************************************************************/

Image_::Image_( int size) : size( size )
{
    image = new QImage*[size * size];
    for (int i = 0; i < (size * size); i++)
        image[i] = 0;    
}

/**************************************************************************************************************************/
/* DESTRUCTOR *************************************************************************************************************/

Image_::~Image_()
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

QImage** Image_::getImage()
{
    return image;
}

/***************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE TO BE LOADED IN SCALE MODE IS LOADABLE ************************************************************/

void Image_::prepareScaledImage( QImage* image, State& state, QString* message, const QMap<QString,QString>* labels )
{
    if (( image->height() >= state.resolution ) && (image->width() >= state.resolution ))
    {
        if ( setImage( new QImage( image->scaled( state.resolution, state.resolution )), state.size ))
        {
            state.loaded = true;
            message->append( labels->value("success") + state.message );
        }
        else
            message->append(labels->value("failure") + state.message );
    }
    else
        message->append(labels->value("toLow") + state.message );
}

/***************************************************************************************************************************/
/* CHECK WHETHER AN IMAGE TO BE LOADED IN CROP MODE IS LOADABLE ************************************************************/

void Image_::prepareCroppedImage( QImage* image, State& state, QString* message, const QMap<QString,QString>* labels )
{
    if (( image->height() >= state.resolution ) && (image->width() >= state.resolution ))
    {
        if ( setImage( new QImage(image->copy(( image->width() - state.resolution)/2, ( image->height() - state.resolution )/2, state.resolution, state.resolution )), state.size ))
        {
            state.loaded = true;
            message->append( labels->value("success") + state.message );
        }
        else
            message->append(labels->value("failure") + state.message );
    }
    else
        message->append(labels->value("toLow") + state.message );
}

/**************************************************************************************************************************/
/* RESTORE SAVED IMAGE BOARD **********************************************************************************************/

/*
bool Image_::restoreImageFromFile( uchar* bufferImage, int size )
{
    QImage** image;

    if ( size == 4 )
        image = imageFour;
    else if ( size == 5 )
        image = imageFive;
    else if ( size == 6 )
        image = imageSix;
    else if ( size == 7 )
        image = imageSeven;

    try
    {
        for ( int i = 0; i < size * size; i++ )
            image[i] = new QImage( bufferImage + i * 10000, 50, 50, QImage::Format_RGB32 );
    }
    catch(...)
    {
        return false;
    }
    return true;
}
*/
/**************************************************************************************************************************/
/* MAKE IMAGE FOR EACH SQUARE *********************************************************************************************/

bool Image_::setImage(QImage* imageWhole, int size)
{
    // Settings white (empty) image
    image[0] = new QImage(50,50, QImage::Format_RGB32);
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
            image[0]->setPixel(i, j, qRgb(255, 255, 255));
    }

    int x = 0;

    for (int i = 0; i < size * 50; i += 50)
    {
        for (int j = 0; j < size * 50; j +=50)
        {
            if ((i == size * 50 - 50) && (j == size * 50 - 50))
                return true;

            try
            {
                image[++x] = new QImage(50, 50, QImage::Format_RGB32);

                for (int k = 0; k < 50; k++)
                {
                    for (int l = 0; l < 50; l++)
                        image[x]->setPixel(k,l, imageWhole->pixel(k + j ,l + i));
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

