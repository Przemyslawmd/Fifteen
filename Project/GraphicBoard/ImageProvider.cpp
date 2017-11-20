
#include "ImageProvider.h"
#include "../Options.h"

/********************************************************************************/
/* GET IMAGE PROVIDER INSTANCE **************************************************/

ImageProvider& ImageProvider::getInstance()
{
    if ( instance == nullptr )
        instance = new ImageProvider();

    return *instance;
}

/*********************************************************************************/
/* DELETE IMAGE PROVIDER INSTANCE ************************************************/

void ImageProvider::deleteInstance()
{
    if ( instance == nullptr )
        return;

    delete instance;
    instance = nullptr;
}

/***********************************************************************************/
/***********************************************************************************/

ImageProvider::ImageProvider()
{
    images = new GraphicBoard*[countImages];

    for ( int i = 0; i < countImages; i++ )
        images[i] = nullptr;

    isImageFour = false;
    isImageFive = false;
    isImageSix = false;
    isImageSeven = false;
}

/************************************************************************************/
/************************************************************************************/

ImageProvider::~ImageProvider()
{
    for ( int i = 0; i < countImages; i++ )
    {
        if ( images[i] != nullptr )
            delete images[i];
    }

    delete [] images;
}

/**************************************************************************************/
/* PREPARE BOARD IMAGE ****************************************************************/

void ImageProvider::prepareBoardImage( QImage& image, QString& message, SquareSize squareSize )
{
    imageSquareSize = squareSize;
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createScaled : &GraphicBoard::createCropped;

    if (( Options::isImageToBeLoaded( BoardSize::FOUR )) && ( checkImageSize( image, BoardSize::FOUR, squareSize, message )))
    {
        images[Index::four] = new GraphicBoard( BoardSize::FOUR );
        isImageFour = ( images[Index::four]->*createImage )( image, BoardSize::FOUR, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::FIVE )) && ( checkImageSize( image, BoardSize::FIVE, squareSize, message )))
    {
        images[Index::five] = new GraphicBoard( BoardSize::FIVE );
        isImageFive = ( images[Index::five]->*createImage )( image, BoardSize::FIVE, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SIX )) && ( checkImageSize( image, BoardSize::SIX, squareSize, message )))
    {
        images[Index::six] = new GraphicBoard( BoardSize::SIX );
        isImageSix = ( images[Index::six]->*createImage )( image, BoardSize::SIX, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SEVEN )) && ( checkImageSize( image, BoardSize::SEVEN, squareSize, message )))
    {
        images[Index::seven] = new GraphicBoard( BoardSize::SEVEN );
        isImageSeven = ( images[Index::seven]->*createImage )( image, BoardSize::SEVEN, squareSize );
    }
}

/******************************************************************************************/
/* CHECK SIZE OF PICTURE BEFORE PREPARING GRAPHIC BOARD ***********************************/

bool ImageProvider::checkImageSize( QImage& picture, BoardSize size, SquareSize squareSize, QString& message )
{
    if (( picture.height() < size * squareSize ) || ( picture.width() < size * squareSize ))
    {
        message.append( QString ( "Too low size of graphic for a board of size %1 \t\n\n" ).arg( size ));
        return false;
    }

    return true;
}

/*****************************************************************************************/
/* GET IMAGES ****************************************************************************/

QImage** ImageProvider::getImage( int boardSize )
{
    return images[boardSize - countImages]->getImage();
}

/*****************************************************************************************/
/* IS IMAGE ******************************************************************************/

bool ImageProvider::isImage( BoardSize size )
{
    if ( size == BoardSize::FOUR )
        return isImageFour;
    else if ( size == BoardSize::FIVE )
        return isImageFive;
    else if ( size == BoardSize::SIX )
        return isImageSix;
    else
        return isImageSeven;
}

/*****************************************************************************************/
/* GET IMAGE SQUARE SIZE *****************************************************************/

SquareSize ImageProvider::getImageSquareSize()
{
    return imageSquareSize;
}

/*******************************************************************************************/
/* RESTORE IMAGE FROM BOARD ****************************************************************/

void ImageProvider::restoreImageBoardFromFile( uchar* data, int boardSize, SquareSize imageSize, int byteCount )
{
    images[boardSize - countImages] = new GraphicBoard( boardSize * boardSize );
    bool result = images[boardSize - 4]->restoreImagesFromFile( data, imageSize, byteCount );

    if ( result )
        imageSquareSize = imageSize;

    if ( boardSize == 4 )
        isImageFour = result;
    else if ( boardSize == 5 )
        isImageFive = result;
    else if ( boardSize == 6 )
        isImageSix = result;
    else
        isImageSeven = result;
}

/*********************************************************************************************/
/*********************************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

