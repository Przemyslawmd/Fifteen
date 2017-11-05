
#include "IOFile.h"

IOFile::IOFile(){}

/*********************************************************************************/
/* SAVE NUMERIC BOARD IN FILE ****************************************************/

void IOFile::saveNumericBoardInFile( Board* board, QString fileName )
{
    QFile file( fileName );
    QDataStream& stream = getDataStream( file, QIODevice::WriteOnly );

    stream << ( int ) BoardMode::NUMERIC;
    stream << board->getCurrentSize();

    insertBoardValuesIntoStream( stream, board );
    file.close();
}

/*********************************************************************************/
/* SAVE GRAPHIC BOARD IN FILE ****************************************************/

void IOFile::saveGraphicBoardInFile( Board* board, ImagesState* images, QString fileName )
{
    QFile file( fileName );
    QDataStream& inData = getDataStream( file, QIODevice::WriteOnly );

    inData << ( int ) BoardMode::GRAPHIC;
    int boardSize = board->getCurrentSize();
    inData << boardSize;

    insertBoardValuesIntoStream( inData, board );

    inData << ( quint32 )images->imageSize;
    QImage** pictures = ImageProvider::getInstance()->getImage( boardSize );
    int byteCount = pictures[0]->byteCount();
    inData << byteCount;
    uchar* buffer = new uchar[ byteCount ];

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        memcpy( buffer, pictures[i]->bits(), byteCount );
        inData.writeRawData( (char*)buffer, byteCount );
    }
    delete [] buffer;

    file.close();
}

/*********************************************************************************/
/* READ BOARD FROM FILE **********************************************************/

int** IOFile::readBoardFromFile( QString fileName, ImagesState* images )
{
    QFile file( fileName );
    QDataStream& stream = getDataStream( file, QIODevice::ReadOnly );

    int boardMode;
    int level;

    stream >> boardMode;
    stream >> level;

    Options::setBoardSize( static_cast< BoardSize >( level ));

    int** values = new int*[level];
    for (int i = 0; i < level; i++)
    {
        values[i] = new int[level];
        for (int j = 0; j < level; j++)
             stream >> values[i][j];
    }

    if ( boardMode == ( int )BoardMode::NUMERIC )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
        int imageSize;
        stream >> imageSize;
        images->imageSize = ( SquareSize )imageSize;
        int byteCount;
        stream >> byteCount;

        // This buffer is moved to an Image object which is responsible for release memory
        // and must exist as long as restored image exists
        uchar* buffer = new uchar[byteCount * level * level];
        for ( int i = 0; i < ( level  * level ); i++ )
            stream.readRawData( (char*)( buffer + i * byteCount ), byteCount );

        ImageProvider::deleteInstance();
        ImageProvider* imageProvider = ImageProvider::getInstance();

        if ( level == BoardSize::FOUR )
            images->four.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
        else if ( level == BoardSize::FIVE )
            images->five.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
        else if ( level == BoardSize::SIX )
            images->six.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
        else
            images->seven.loaded = imageProvider->restoreImageBoardFromFile( buffer, level, images->imageSize, byteCount );
    }

    file.close();
    return values;
}

/*********************************************************************************/
/* GET DATA STREAM ***************************************************************/

QDataStream& IOFile::getDataStream( QFile& file, QIODevice::OpenModeFlag mode )
{
    file.open( mode );
    QDataStream* stream = new QDataStream( &file );
    stream->setVersion( QDataStream::Qt_4_6 );
    return *stream;
}

/*********************************************************************************/
/* INSERT BOARD VALUES INTO STREAM ***********************************************/

void IOFile::insertBoardValuesIntoStream( QDataStream& stream, Board* board )
{
    int** values = board->sendBoard();
    int size = board->getCurrentSize();

    for ( int i = 0; i < size; i++ )
    {
        for ( int j = 0; j < size; j++ )
            stream << values[i][j];
    }
}



