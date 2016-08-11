#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <ImageLoad.h>
#include <QImage>
#include <Image_.h>
#include <Types.h>

class ImageProvider
{
public:

    ImageProvider();
    ~ImageProvider();

    QImage** getImage( int );
    void prepareBoardImage( QImage*, QString*, const QMap<QString, QString>*, ImageLoad&, bool );

private:

    enum index { FOUR, FIVE, SIX, SEVEN };

    Image_* images[4];
    Image_* imageFour;
    Image_* imageFive;
    Image_* imageSix;
    Image_* imageSeven;

    void ( Image_::*pPrepareImage )( QImage*, State&, QString*, const QMap<QString,QString>* );

};

#endif // IMAGEPROVIDER_H
