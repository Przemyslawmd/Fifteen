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
    //QImage** getImageFive();
    //QImage** getImageSix();
    //QImage** getImageSeven();

    //void prepareImagesForBoard( QImage*, QString*, const QMap<QString, QString>*, ImageLoad&, bool );
    //bool restoreImageFromFile( uchar*, int );

private:

    int size;
    bool setImage(QImage*, int );
    bool tryImage();

    // One dimension array with QImage pointers
    QImage** image;
    //QImage** imageFive;
    //QImage** imageSix;
    //QImage** imageSeven;

    friend class ImageProvider;

    void prepareScaledImage( QImage*, State&, QString*, const QMap<QString,QString>* );
    void prepareCroppedImage( QImage*, State&, QString*, const QMap<QString,QString>* );
    //void ( Image_::*pPrepareImage )( QImage*, QImage***, State&, QString*, const QMap<QString,QString>* );
};

#endif // IMAGE__H
