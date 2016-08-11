#include "ImageProvider.h"

ImageProvider::ImageProvider()
{
    //imageFour = new QImage*[16];
    //for (int i = 0; i < 16; i++)
     //   imageFour[i] = 0;

    images = new Image_*[4];

    for ( int i = 0; i < 4; i++ )
        images[i] = nullptr;
}

ImageProvider::~ImageProvider()
{
    for ( int i = 0; i < 4; i++ )
    {
        if ( images[i] != nullptr )
            delete images[i];
    }

    delete [] images;

}

void ImageProvider::prepareBoardImage( QImage* image, QString* message, const QMap<QString,QString>* labels, ImageLoad& imageState, bool isScaled )
{
    pPrepareImage = ( isScaled ) ? &Image_::prepareScaledImage : &Image_::prepareCroppedImage;

    if ( imageState.four.toLoad )
    {
        images[FOUR] = new Image_( imageState.four.size );
        ( images[FOUR]->*pPrepareImage )( image, imageState.four, message, labels );
    }

    if ( imageState.five.toLoad )
    {
        images[FIVE] = new Image_( imageState.five.size );
        ( images[FIVE]->*pPrepareImage )( image, imageState.five, message, labels );
    }

    if ( imageState.six.toLoad )
    {
        images[SIX] = new Image_( imageState.six.size );
        ( images[SIX]->*pPrepareImage )( image, imageState.six, message, labels );
    }

    if ( imageState.seven.toLoad )
    {
        images[SEVEN] = new Image_( imageState.seven.size );
        ( images[SEVEN]->*pPrepareImage )( image, imageState.seven, message, labels );
    }

}

QImage** ImageProvider::getImage( int size )
{
    return images[size - 4]->getImage();
}

bool ImageProvider::restoreImageBoardFromFile( uchar* data, int size )
{
    images[size - 4] = new Image_( size * size );
    return images[size - 4]->restoreImagesFromFile( data );
}

