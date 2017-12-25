
#include "IOFile.h"
#include "Options.h"
#include "GraphicBoard/ImageProvider.h"
#include <memory>

using std::unique_ptr;

IOFile::IOFile(){}

/*********************************************************************************/
/* SAVE NUMERIC BOARD IN FILE ****************************************************/

void IOFile::saveNumericBoardInFile( Board* board, QString fileName )
{
    QFile file( fileName );
    unique_ptr<QDataStream> stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << (int) BoardMode::NUMERIC;
    *stream << board->getCurrentSize();

    stream = insertBoardValuesIntoStream( std::move( stream ), board );
    file.close();
}

/*********************************************************************************/
/* SAVE GRAPHIC BOARD IN FILE ****************************************************/

void IOFile::saveGraphicBoardInFile( Board* board, QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << (int) BoardMode::GRAPHIC;
    int boardSize = board->getCurrentSize();
    *stream << boardSize;

    stream = insertBoardValuesIntoStream( std::move( stream ), board );

    ImageProvider& provider = ImageProvider::getInstance();
    *stream << (int) provider.getImageSquareSize();
    QImage** pictures = provider.getImage( (BoardSize) boardSize );
    int byteCount = pictures[0]->byteCount();
    *stream << byteCount;
    uchar* buffer = new uchar[ byteCount ];

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        memcpy( buffer, pictures[i]->bits(), byteCount );
        stream->writeRawData( (char*)buffer, byteCount );
    }
    delete [] buffer;

    file.close();
}

/*********************************************************************************/
/* READ BOARD FROM FILE **********************************************************/

unique_ptr< vector<int> > IOFile::readBoardFromFile( QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::ReadOnly );

    int boardMode;
    *stream >> boardMode;
    int level;
    *stream >> level;

    unique_ptr< vector<int> > values( new vector<int> );
    int temp;
    for ( int i = 0; i < level * level ; i++ )
    {
        *stream >> temp;
        values->push_back( temp );
    }

    if ( boardMode == (int) BoardMode::NUMERIC )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
        ImageProvider::deleteInstance();
        ImageProvider& imageProvider = ImageProvider::getInstance();
        imageProvider.restoreImageBoardFromFile( std::move( stream ), (BoardSize) level );
    }

    file.close();
    values->push_back( level );
    return values;
}

/*********************************************************************************/
/* GET DATA STREAM ***************************************************************/

unique_ptr<QDataStream> IOFile::getDataStream( QFile& file, QIODevice::OpenModeFlag mode )
{
    file.open( mode );
    unique_ptr< QDataStream > stream( new QDataStream( &file ));
    stream->setVersion( QDataStream::Qt_4_6 );
    return stream;
}

/*********************************************************************************/
/* INSERT BOARD VALUES INTO STREAM ***********************************************/

unique_ptr< QDataStream > IOFile::insertBoardValuesIntoStream( unique_ptr< QDataStream > stream, Board* board )
{
    vector<int>& values = board->sendBoard();
    int size = board->getCurrentSize();

    for ( int i = 0; i < size * size; i++ )
    {
        *stream << values.at( i );
    }

    return stream;
}
