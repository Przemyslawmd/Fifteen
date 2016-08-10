#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <ImageLoad.h>
#include <QImage>
#include <Image_.h>

class ImageProvider
{
public:

    ImageProvider();

    QImage** getImage( int );
    void prepareImagesForBoard( QImage*, QString*, const QMap<QString, QString>*, ImageLoad&, bool );

private:

    Image_* imageFour;
    Image_* imageFive;
    Image_* imageSix;
    Image_* imageSeven;

    void ( Image_::*pPrepareImage )( QImage*, State&, QString*, const QMap<QString,QString>* );

};

#endif // IMAGEPROVIDER_H
