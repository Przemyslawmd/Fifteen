#include "ImageProvider.h"

ImageProvider::ImageProvider()
{
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
