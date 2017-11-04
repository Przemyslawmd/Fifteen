
#include "IOFile.h"

/*********************************************************************************/
/* SAVE NUMERIC BOARD IN FILE ****************************************************/

void IOFile::saveNumericBoardInFile( Board* board, QString fileName )
{
    QFile file( fileName );
    QDataStream& stream = getDataStream( file );

    stream << 1;
    BoardSize boardSize = Options::getBoardSize();
    stream << boardSize;

    insertBoardValuesIntoStream( stream, board, boardSize );
    file.close();
}

/*********************************************************************************/
/* SAVE GRAPHIC BOARD IN FILE ****************************************************/

void IOFile::saveGraphicBoardInFile( Board* board, ImagesState* images, QString fileName )
{
    QFile file( fileName );
    QDataStream& inData = getDataStream( file );

    inData << 0;
    BoardSize boardSize = Options::getBoardSize();
    inData << boardSize;

    insertBoardValuesIntoStream( inData, board, boardSize );

    inData << ( quint32 )images->imageSize;
    QImage** pictures = ImageProvider::getInstance()->getImage( boardSize );
    int byteCount = pictures[0]->byteCount();
    inData << byteCount;
    uchar* buffer = new uchar[ byteCount ];

    for (int i = 0; i < boardSize * boardSize; i++)
    {
        memcpy( buffer, pictures[i]->bits(), byteCount );
        inData.writeRawData( (char*)buffer, byteCount );
    }
    delete [] buffer;

    file.close();
}

/*********************************************************************************/
/* GET DATA STREAM ***************************************************************/

QDataStream& IOFile::getDataStream( QFile& file )
{
    file.open( QIODevice::WriteOnly );
    QDataStream* stream = new QDataStream( &file );
    stream->setVersion( QDataStream::Qt_4_6 );
    return *stream;
}

/*********************************************************************************/
/* INSERT BOARD VALUES INTO STREAM ***********************************************/

void IOFile::insertBoardValuesIntoStream( QDataStream& stream, Board* board, BoardSize boardSize )
{
    int** values = board->sendBoard();
    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
            stream << values[i][j];
    }
}


void IOFile::readBoardFromFile()
{}
