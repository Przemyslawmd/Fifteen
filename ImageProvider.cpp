#include "ImageProvider.h"

ImageProvider::ImageProvider()
{

}

void ImageProvider::prepareImagesForBoard( QImage* image, QString* message, const QMap<QString,QString>* labels, ImageLoad& imageState, bool isScaled )
{
    pPrepareImage = ( isScaled ) ? &Image_::prepareScaledImage : &Image_::prepareCroppedImage;

    if ( imageState.four.toLoad )
    {
        imageFour = new Image_();
        ( imageFour->*pPrepareImage )( image, imageState.four, message, labels );
    }

    if ( imageState.five.toLoad )
        ( imageFive->*pPrepareImage )( image, imageState.five, message, labels );

    if ( imageState.six.toLoad )
        ( imageSix->*pPrepareImage )( image, imageState.six, message, labels );

    if ( imageState.seven.toLoad )
        ( imageSeven->*pPrepareImage )( image, imageState.seven, message, labels );

}
