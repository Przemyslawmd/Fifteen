#ifndef IMAGE_H
#define IMAGE_H
#include <QImage>
#include <QMap>
#include <ImageLoad.h>

class Image
{
public:
    Image();
    ~Image();

    QImage** getImageFour();
    QImage** getImageFive();
    QImage** getImageSix();
    QImage** getImageSeven();

    void prepareImagesForBoard( QImage*, QString*, const QMap<QString, QString>*, ImageLoad&, bool );
    bool restoreImageFromFile( uchar*, int );

private:

    bool setImage(QImage*, QImage***, int);

    // One dimension array with QImage pointers
    QImage** imageFour;
    QImage** imageFive;
    QImage** imageSix;
    QImage** imageSeven;    

    void prepareScaledImage( QImage*, QImage***, State&, QString*, const QMap<QString,QString>* );
    void prepareCroppedImage( QImage*, QImage***, State&, QString*, const QMap<QString,QString>* );
    void ( Image::*pPrepareImage )( QImage*, QImage***, State&, QString*, const QMap<QString,QString>* );
};

#endif // IMAGE_H
