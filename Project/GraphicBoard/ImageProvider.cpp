
#include "ImageProvider.h"

/********************************************************************************/
/* GET IMAGE PROVIDER INSTANCE **************************************************/

ImageProvider* ImageProvider::getInstance()
{
    if ( instance == nullptr )
        instance = new ImageProvider();

    return instance;
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

void ImageProvider::prepareBoardImage( QImage& image, QString& message, ImagesState& imageState, SquareSize squareSize )
{
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createScaled : &GraphicBoard::createCropped;

    if (( Options::isImageToBeLoaded( BoardSize::FOUR )) && ( checkImageSize( image, imageState.four, squareSize, message )))
    {
        images[Index::four] = new GraphicBoard( imageState.four.size );
        ( images[Index::four]->*createImage )( image, imageState.four, message, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::FIVE )) && ( checkImageSize( image, imageState.five, squareSize, message )))
    {
        images[Index::five] = new GraphicBoard( imageState.five.size );
        ( images[Index::five]->*createImage )( image, imageState.five, message, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SIX )) && ( checkImageSize( image, imageState.six, squareSize, message )))
    {
        images[Index::six] = new GraphicBoard( imageState.six.size );
        ( images[Index::six]->*createImage )( image, imageState.six, message, squareSize );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SEVEN )) && ( checkImageSize( image, imageState.seven, squareSize, message )))
    {
        images[Index::seven] = new GraphicBoard( imageState.seven.size );
        ( images[Index::seven]->*createImage )( image, imageState.seven, message, squareSize );
    }
}

/******************************************************************************************/
/* CHECK SIZE OF PICTURE BEFORE PREPARING GRAPHIC BOARD ***********************************/

bool ImageProvider::checkImageSize( QImage& picture, State& state, SquareSize squareSize, QString& message )
{
    if (( picture.height() < state.size * squareSize ) || ( picture.width() < state.size * squareSize ))
    {
        message.append( QString ( "Too low size of graphic for a board of size %1 \t\n\n" ).arg( state.size ));
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

/*******************************************************************************************/
/* RESTORE IMAGE FROM BOARD ****************************************************************/

bool ImageProvider::restoreImageBoardFromFile( uchar* data, int boardSize, SquareSize imageSize, int byteCount )
{
    images[boardSize - countImages] = new GraphicBoard( boardSize * boardSize );
    return images[boardSize - 4]->restoreImagesFromFile( data, imageSize, byteCount );
}

/*********************************************************************************************/
/*********************************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

