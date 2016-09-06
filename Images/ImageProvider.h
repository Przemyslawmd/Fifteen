#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <Images/ImageLoad.h>
#include <QImage>
#include <Images/Image.h>
#include <Types.h>

class ImageProvider
{
public:

    static ImageProvider* getInstance();
    static void deleteInstance();

    QImage** getImage( int );
    void prepareBoardImage( QImage*, QString*, ImageLoad&, bool );
    bool restoreImageBoardFromFile( uchar*, int );

private:

    ImageProvider();
    ~ImageProvider();

    void ( Image::*pPrepareImage )( QImage*, State&, QString*  );

    enum index { FOUR = 0, FIVE, SIX, SEVEN };
    const int COUNT = 4;

    Image** images;
    static ImageProvider* instance;
};

#endif // IMAGEPROVIDER_H
