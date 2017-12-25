
#include "ImageProvider.h"
#include "../Options.h"
#include "../Message.h"

/********************************************************************************/
/* GET INSTANCE *****************************************************************/

ImageProvider& ImageProvider::getInstance()
{
    if ( instance == nullptr )
        instance = new ImageProvider();

    return *instance;
}

/*********************************************************************************/
/* DELETE INSTANCE ***************************************************************/

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
    boardFour = nullptr;
    boardFive = nullptr;
    boardSix = nullptr;
    boardSeven = nullptr;
}

/************************************************************************************/
/************************************************************************************/

ImageProvider::~ImageProvider()
{
    removeBoard( &boardFour );
    removeBoard( &boardFive );
    removeBoard( &boardSix );
    removeBoard( &boardSeven );
}

/**************************************************************************************/
/* PREPARE BOARD IMAGE ****************************************************************/

void ImageProvider::prepareBoardImage( QImage& image, SquareSize squareSize )
{
    imageSquareSize = squareSize;
    createImage = ( Options::getGraphicMode() == GraphicMode::SCALED ) ? &GraphicBoard::createScaled : &GraphicBoard::createCropped;

    if (( Options::isImageToBeLoaded( BoardSize::FOUR )) && ( checkImageSize( image, BoardSize::FOUR, squareSize )))
    {
        boardFour = new GraphicBoard( BoardSize::FOUR );
        if (( boardFour->*createImage )( image, BoardSize::FOUR, squareSize ) == false )
            removeBoard( &boardFour );
    }

    if (( Options::isImageToBeLoaded( BoardSize::FIVE )) && ( checkImageSize( image, BoardSize::FIVE, squareSize )))
    {
        boardFive = new GraphicBoard( BoardSize::FIVE );
        if (( boardFive->*createImage )( image, BoardSize::FIVE, squareSize ) == false )
            removeBoard( &boardFive );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SIX )) && ( checkImageSize( image, BoardSize::SIX, squareSize )))
    {
        boardSix = new GraphicBoard( BoardSize::SIX );
        if (( boardSix->*createImage )( image, BoardSize::SIX, squareSize ) == false )
            removeBoard( &boardSix );
    }

    if (( Options::isImageToBeLoaded( BoardSize::SEVEN )) && ( checkImageSize( image, BoardSize::SEVEN, squareSize )))
    {
        boardSeven = new GraphicBoard( BoardSize::SEVEN );
        if (( boardSeven->*createImage )( image, BoardSize::SEVEN, squareSize ) == false )
            removeBoard( &boardSeven );
    }
}

/******************************************************************************************/
/* CHECK IMAGE SIZE ***********************************************************************/

bool ImageProvider::checkImageSize( QImage& picture, BoardSize boardSize, SquareSize squareSize )
{
    if (( picture.height() < boardSize * squareSize ) || ( picture.width() < boardSize * squareSize ))
    {
        Message::putMessage( MessageCode::GRAPHIC_TOO_LOW_SIZE, boardSize );
        return false;
    }

    return true;
}

/*****************************************************************************************/
/* GET IMAGE *****************************************************************************/

QImage** ImageProvider::getImage( BoardSize boardSize )
{
    return selectBoard( boardSize )->getImage();
}

/*****************************************************************************************/
/* IS IMAGE ******************************************************************************/

bool ImageProvider::isImage( BoardSize boardSize )
{
    return selectBoard( boardSize ) != nullptr;
}

/*****************************************************************************************/
/* GET IMAGE SQUARE SIZE *****************************************************************/

SquareSize ImageProvider::getImageSquareSize()
{
    return imageSquareSize;
}

/*******************************************************************************************/
/* RESTORE IMAGE BOARD FROM FILE ***********************************************************/

void ImageProvider::restoreImageBoardFromFile( unique_ptr< QDataStream > stream, BoardSize boardSize )
{
    GraphicBoard** board = selectBoardPointer( boardSize );
    *board = new GraphicBoard( boardSize );

    int imageSize;
    *stream >> imageSize;
    int byteCount;
    *stream >> byteCount;

    uchar* buffer = new uchar[byteCount * boardSize * boardSize];
    for ( int i = 0; i < ( boardSize  * boardSize ); i++ )
        stream->readRawData( (char*) ( buffer + i * byteCount ), byteCount );

    if ( (*board)->restoreImagesFromFile( buffer, (SquareSize) imageSize, byteCount ))
    {
        imageSquareSize = (SquareSize) imageSize;
    }
    else
    {
        delete *board;
        *board = nullptr;
    }
}

/*********************************************************************************************/
/* SELECT BOARD ******************************************************************************/

GraphicBoard* ImageProvider::selectBoard( BoardSize size )
{
    if ( size == BoardSize::FOUR )
        return boardFour;
    else if ( size == BoardSize::FIVE )
        return boardFive;
    else if ( size == BoardSize::SIX )
        return boardSix;
    else
        return boardSeven;
}

/*********************************************************************************************/
/* SELECT BOARD POINTER **********************************************************************/

GraphicBoard** ImageProvider::selectBoardPointer( BoardSize size )
{
    if ( size == BoardSize::FOUR )
        return &boardFour;
    else if ( size == BoardSize::FIVE )
        return &boardFive;
    else if ( size == BoardSize::SIX )
        return &boardSix;
    else
        return &boardSeven;
}

/*********************************************************************************************/
/* REMOVE BOARD ******************************************************************************/

void ImageProvider::removeBoard( GraphicBoard** board )
{
    if ( board != nullptr && *board != nullptr )
    {
        delete *board;
        *board = nullptr;
    }
}

/*********************************************************************************************/
/*********************************************************************************************/

ImageProvider* ImageProvider::instance = nullptr;

