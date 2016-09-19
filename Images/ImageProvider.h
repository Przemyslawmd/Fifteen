#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <Images/ImageLoad.h>
#include <QImage>
#include <Images/Image.h>
#include <Types.h>
#include <Options.h>

class ImageProvider
{
public:

    static ImageProvider* getInstance();
    static void deleteInstance();

    QImage** getImage( int );
    void prepareBoardImage( QImage*, QString*, ImageLoad&, SquareSize );
    bool restoreImageBoardFromFile( uchar*, int, SquareSize );

private:

    ImageProvider();
    ~ImageProvider();

    void ( Image::*pPrepareImage )( QImage*, State&, QString*, SquareSize );

    enum index { FOUR = 0, FIVE, SIX, SEVEN };
    const int COUNT = 4;

    Image** images;
    static ImageProvider* instance;
};

#endif // IMAGEPROVIDER_H
