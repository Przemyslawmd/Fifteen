
#include "IOFile.h"
#include "Options.h"
#include "Message.h"
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
    vector< QImage* >* pictures = provider.getImages( (BoardSize) boardSize );
    int byteCount = pictures->at( 0 )->byteCount();
    *stream << byteCount;
    uchar* buffer = new uchar[ byteCount ];

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        memcpy( buffer, pictures->at( i )->bits(), byteCount );
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
    if ( boardMode != (int) BoardMode::GRAPHIC && boardMode != (int) BoardMode::NUMERIC )
    {
        Message::putMessage( MessageCode::READ_BOARD_TYPE_ERROR );
        return nullptr;
    }

    int level;
    *stream >> level;
    if ( level < (int) BoardSize::FOUR || level > (int) BoardSize::SEVEN )
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        return nullptr;
    }

    unique_ptr< vector<int> > values( new vector<int> );
    int temp;
    for ( int i = 0; i < level * level ; i++ )
    {
        *stream >> temp;
        values->push_back( temp );
    }

    values = checkReadValues( std::move( values ), (BoardSize) level );
    if ( values == nullptr )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
        return nullptr;
    }

    if ( boardMode == (int) BoardMode::NUMERIC )
    {
        Options::setBoardMode( BoardMode::NUMERIC );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
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

/*********************************************************************************/
/* CHECK READ VALUES *************************************************************/

unique_ptr< vector<int> > IOFile::checkReadValues( unique_ptr< vector<int> > valuesRead, BoardSize boardSize )
{
    vector<int> valuesToCompare;

    for ( int i = 0; i < boardSize * boardSize; i++ )
        valuesToCompare.push_back( i );

    for ( int value : *valuesRead )
    {
        auto it = std::find( std::begin( valuesToCompare ), std::end( valuesToCompare ), value );

        if ( it == std::end( valuesToCompare ))
            return nullptr;
        else
            valuesToCompare.erase( it );
    }
    return valuesRead;
}

