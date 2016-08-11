#ifndef IMAGE__H
#define IMAGE__H

#include <QImage>
#include <QMap>
#include <ImageLoad.h>

class ImageProvider;

class Image_
{
public:
    Image_( int size );
    ~Image_();

    QImage** getImage();

private:

    friend class ImageProvider;

    int size;
    QImage** image;

    bool setImage(QImage*, int );
    bool restoreImagesFromFile( uchar* );

    void prepareScaledImage( QImage*, State&, QString*, const QMap<QString,QString>* );
    void prepareCroppedImage( QImage*, State&, QString*, const QMap<QString,QString>* );    
};

#endif // IMAGE__H
