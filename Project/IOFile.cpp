
#include "IOFile.h"
#include "Options.h"
#include "Message.h"
#include "GraphicBoard/ImageProvider.h"
#include <memory>

using std::unique_ptr;

IOFile::IOFile(){}

/*********************************************************************************/
/*********************************************************************************/

void IOFile::saveNumericBoardInFile( Board& board, QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << (int) BoardMode::NUMERIC;
    *stream << board.getCurrentSize();

    stream = insertBoardValuesIntoStream( std::move( stream ), board );

    file.close();
}

/*********************************************************************************/
/*********************************************************************************/

void IOFile::saveGraphicBoardInFile( Board& board, QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << (int) BoardMode::GRAPHIC;
    int boardSize = board.getCurrentSize();
    *stream << boardSize;

    stream = insertBoardValuesIntoStream( std::move( stream ), board );

    ImageProvider& provider = ImageProvider::getInstance();
    *stream << (int) provider.getImageSquareSize();
    vector< QImage* >& pictures = provider.getImages( (BoardSize) boardSize );
    int byteCount = pictures.at( 0 )->byteCount();
    *stream << byteCount;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        stream->writeRawData( (char*) pictures.at( i )->bits(), byteCount );
    }

    file.close();
}

/*********************************************************************************/
/*********************************************************************************/

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
        file.close();
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
        file.close();
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

        if ( imageProvider.restoreImageBoardFromFile( std::move( stream ), (BoardSize) level ) == false )
        {
            file.close();
            return nullptr;
        }
    }

    file.close();
    values->push_back( level );
    return values;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr<QDataStream> IOFile::getDataStream( QFile& file, QIODevice::OpenModeFlag mode )
{
    file.open( mode );
    unique_ptr< QDataStream > stream( new QDataStream( &file ));
    stream->setVersion( QDataStream::Qt_4_6 );
    return stream;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< QDataStream > IOFile::insertBoardValuesIntoStream( unique_ptr< QDataStream > stream, Board& board )
{
    vector< int >& values = board.sendBoard();

    for ( auto iter = values.begin(); iter != values.end(); iter++ )
    {
        *stream << *iter;
    }

    return stream;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< vector<int> > IOFile::checkReadValues( unique_ptr< vector<int> > readValues, BoardSize boardSize )
{
    vector<int> valuesToCompare;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        valuesToCompare.push_back( i );
    }

    for ( int value : *readValues )
    {
        auto it = std::find( std::begin( valuesToCompare ), std::end( valuesToCompare ), value );

        if ( it == std::end( valuesToCompare ))
        {
            return nullptr;
        }

        valuesToCompare.erase( it );
    }
    return readValues;
}

