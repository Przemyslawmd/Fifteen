#include "GraphicBoard/ImageProvider.h"

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
    images = new GraphicBoard*[COUNT];

    for ( int i = 0; i < COUNT; i++ )
        images[i] = nullptr;
}

/************************************************************************************/
/************************************************************************************/

ImageProvider::~ImageProvider()
{
    for ( int i = 0; i < COUNT; i++ )
    {
        if ( images[i] != nullptr )
            delete images[i];
    }

    delete [] images;
}

/**************************************************************************************/
/* PREPARE BOARD IMAGE ****************************************************************/

void ImageProvider::prepareBoardImage( QImage& image, QString& message, ImageLoad& imageState, SquareSize squareSize )
{
    pPrepareImage = ( Options::checkScaled() ) ? &GraphicBoard::prepareScaledImage : &GraphicBoard::prepareCroppedImage;

    if (( imageState.four.toLoad ) && ( checkImageSize( image, imageState.four, squareSize, message )))
    {
        images[FOUR] = new GraphicBoard( imageState.four.size );
        ( images[FOUR]->*pPrepareImage )( image, imageState.four, message, squareSize );
    }

    if (( imageState.five.toLoad  ) && ( checkImageSize( image, imageState.five, squareSize, message )))
    {
        images[FIVE] = new GraphicBoard( imageState.five.size );
        ( images[FIVE]->*pPrepareImage )( image, imageState.five, message, squareSize );
    }

    if (( imageState.six.toLoad ) && ( checkImageSize( image, imageState.six, squareSize, message )))
    {
        images[SIX] = new GraphicBoard( imageState.six.size );
        ( images[SIX]->*pPrepareImage )( image, imageState.six, message, squareSize );
    }

    if (( imageState.seven.toLoad ) && ( checkImageSize( image, imageState.seven, squareSize, message )))
    {
        images[SEVEN] = new GraphicBoard( imageState.seven.size );
        ( images[SEVEN]->*pPrepareImage )( image, imageState.seven, message, squareSize );
    }
}

/******************************************************************************************/
/* CHECK SIZE OF PICTURE BEFORE PREPARING GRAPHIC BOARD ***********************************/

bool ImageProvider::checkImageSize( QImage& picture, State& state, SquareSize squareSize, QString& message )
{
    if (( picture.height() < state.size * squareSize ) || ( picture.width() < state.size * squareSize ))
    {
        message.append( "Too low size of graphic for a board " +  state.message );
        return false;
    }

    return true;
}

/*****************************************************************************************/
/* GET IMAGES ****************************************************************************/

QImage** ImageProvider::getImage( int boardSize )
{
    return images[boardSize - COUNT]->getImage();
}

/*******************************************************************************************/
/* RESTORE IMAGE FROM BOARD ****************************************************************/

bool ImageProvider::restoreImageBoardFromFile( uchar* data, int boardSize, SquareSize imageSize, int byteCount )
{
    images[boardSize - COUNT] = new GraphicBoard( boardSize * boardSize );
    return images[boardSize - 4]->restoreImagesFromFile( data, imageSize, byteCount );
}

/*********************************************************************************************/
/*********************************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

