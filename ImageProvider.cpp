#include "ImageProvider.h"

ImageProvider::ImageProvider()
{

}

void ImageProvider::prepareImagesForBoard( QImage* image, QString* message, const QMap<QString,QString>* labels, ImageLoad& imageState, bool isScaled )
{
    pPrepareImage = ( isScaled ) ? &Image_::prepareScaledImage : &Image_::prepareCroppedImage;

    if ( imageState.four.toLoad )
    {
        imageFour = new Image_( imageState.four.size );
        ( imageFour->*pPrepareImage )( image, imageState.four, message, labels );
    }

    if ( imageState.five.toLoad )
    {
        imageFive = new Image_( imageState.five.size );
        ( imageFive->*pPrepareImage )( image, imageState.five, message, labels );
    }

    if ( imageState.six.toLoad )
    {
        imageSix = new Image_( imageState.six.size );
        ( imageSix->*pPrepareImage )( image, imageState.six, message, labels );
    }

    if ( imageState.seven.toLoad )
    {
        imageSeven = new Image_( imageState.seven.size );
        ( imageSeven->*pPrepareImage )( image, imageState.seven, message, labels );
    }

}

QImage** ImageProvider::getImage( int size )
{
    if ( size == 4 )
        return imageFour->getImage();
    return nullptr;

}
