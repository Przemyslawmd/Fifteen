#ifndef IMAGE__H
#define IMAGE__H

#include <QImage>
#include <QMap>
#include <Images/ImageLoad.h>

class ImageProvider;

class Image
{
public:
    Image( int size );
    ~Image();

    QImage** getImage();

private:

    friend class ImageProvider;

    int size;
    QImage** image;
    uchar* bufferRestored;

    bool createSquareImage( QImage*, int, SquareSize );
    bool restoreImagesFromFile( uchar*, SquareSize, int );

    void prepareScaledImage( QImage*, State&, QString&, SquareSize );
    void prepareCroppedImage( QImage*, State&, QString&, SquareSize );
};

#endif // IMAGE__H
