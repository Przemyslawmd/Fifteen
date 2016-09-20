#include "Images/ImageProvider.h"

/********************************************************************************/
/* GET IMAGE PROVIDER INSTANCE **************************************************/

ImageProvider* ImageProvider::getInstance()
{
    if ( instance == nullptr )
        instance = new ImageProvider();

    return instance;
}

/*********************************************************************************/
/* DELETE IMAGE PROVIDER INSTANCE ************************************************/

void ImageProvider::deleteInstance()
{
    if ( instance == nullptr )
        return;

    delete instance;
    instance = nullptr;
}

/***********************************************************************************/
/***********************************************************************************/

ImageProvider::ImageProvider()
{
    images = new Image*[COUNT];

    for ( int i = 0; i < COUNT; i++ )
        images[i] = nullptr;
}

/************************************************************************************/
/************************************************************************************/

ImageProvider::~ImageProvider()
{
    for ( int i = 0; i < COUNT; i++ )
    {
        if ( images[i] != nullptr )
            delete images[i];
    }

    delete [] images;
}

/**************************************************************************************/
/* PREPARE BOARD IMAGE ****************************************************************/

void ImageProvider::prepareBoardImage( QImage* image, QString* message, ImageLoad& imageState, SquareSize squareSize )
{
    pPrepareImage = ( Options::checkScaled() ) ? &Image::prepareScaledImage : &Image::prepareCroppedImage;

    if ( imageState.four.toLoad )
    {
        images[FOUR] = new Image( imageState.four.size );
        ( images[FOUR]->*pPrepareImage )( image, imageState.four, message, squareSize );
    }

    if ( imageState.five.toLoad )
    {
        images[FIVE] = new Image( imageState.five.size );
        ( images[FIVE]->*pPrepareImage )( image, imageState.five, message, squareSize );
    }

    if ( imageState.six.toLoad )
    {
        images[SIX] = new Image( imageState.six.size );
        ( images[SIX]->*pPrepareImage )( image, imageState.six, message, squareSize );
    }

    if ( imageState.seven.toLoad )
    {
        images[SEVEN] = new Image( imageState.seven.size );
        ( images[SEVEN]->*pPrepareImage )( image, imageState.seven, message, squareSize );
    }
}

/*****************************************************************************************/
/* GET IMAGES ****************************************************************************/

QImage** ImageProvider::getImage( int size )
{
    return images[size - COUNT]->getImage();
}

/*******************************************************************************************/
/* RESTORE IMAGE FROM BOARD ****************************************************************/

bool ImageProvider::restoreImageBoardFromFile( uchar* data, int size, SquareSize imageSize, int byteCount )
{
    images[size - COUNT] = new Image( size * size );
    return images[size - 4]->restoreImagesFromFile( data, imageSize, byteCount );
}

/*********************************************************************************************/
/*********************************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;
