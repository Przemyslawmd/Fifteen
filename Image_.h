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

    int size;
    bool setImage(QImage*, int );

    // One dimension array with QImage pointers
    QImage** image;

    friend class ImageProvider;

    void prepareScaledImage( QImage*, State&, QString*, const QMap<QString,QString>* );
    void prepareCroppedImage( QImage*, State&, QString*, const QMap<QString,QString>* );    
};

#endif // IMAGE__H
