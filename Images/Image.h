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

    const int SQUARE_SIZE = 50;

    int size;
    QImage** image;
    uchar* bufferRestored;

    bool createSquareImage( QImage*, int, SquareSize );
    bool restoreImagesFromFile( uchar* );

    void prepareScaledImage( QImage*, State&, QString*, SquareSize );
    void prepareCroppedImage( QImage*, State&, QString*, SquareSize );
};

#endif // IMAGE__H
