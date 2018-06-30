
#include "IOBoard.h"
#include "Options.h"
#include "Message.h"
#include "GraphicBoard/ImageProvider.h"
#include <memory>

using std::unique_ptr;

IOBoard::IOBoard(){}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveNumericBoardInFile( Board& board, QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << static_cast< int >( BoardMode::NUMERIC );
    *stream << board.getCurrentSize();

    stream = insertBoardValuesIntoStream( std::move( stream ), board );

    file.close();
}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveGraphicBoardInFile( Board& board, QString fileName )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::WriteOnly );

    *stream << static_cast< int >( BoardMode::GRAPHIC );
    int boardSize = board.getCurrentSize();
    *stream << boardSize;

    stream = insertBoardValuesIntoStream( std::move( stream ), board );

    ImageProvider& provider = ImageProvider::getInstance();
    *stream << static_cast< int >( provider.getImageSquareSize() );
    vector< QImage* >& pictures = provider.getImages( static_cast< BoardSize >( boardSize ));
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

bool IOBoard::readBoardFromFile( QString fileName, vector< int >& values )
{
    QFile file( fileName );
    unique_ptr< QDataStream > stream = getDataStream( file, QIODevice::ReadOnly );

    int boardMode;
    *stream >> boardMode;
    if ( boardMode != static_cast< int >( BoardMode::GRAPHIC ) && boardMode != static_cast< int >( BoardMode::NUMERIC ))
    {
        Message::putMessage( MessageCode::READ_BOARD_TYPE_ERROR );
        file.close();
        return false;
    }

    int level;
    *stream >> level;
    if ( level < static_cast< int >( BoardSize::FOUR ) || level > static_cast< int >( BoardSize::SEVEN ))
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        file.close();
        return false;
    }

    values.resize( level * level );

    for ( int i = 0; i < level * level ; i++ )
    {
        *stream >> values.at( i );
    }

    if ( checkReadValues( values, static_cast< BoardSize >( level )) == false )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
        file.close();
        return false;
    }

    if ( boardMode == static_cast< int >( BoardMode::NUMERIC ))
    {
        Options::setBoardMode( BoardMode::NUMERIC );
    }
    else
    {
        Options::setBoardMode( BoardMode::GRAPHIC );
        ImageProvider& imageProvider = ImageProvider::getInstance();

        if ( imageProvider.restoreGraphicBoardFromFile( std::move( stream ), static_cast< BoardSize >( level )) == false )
        {
            file.close();
            return false;
        }
    }

    file.close();
    values.push_back( level );
    return true;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< QDataStream > IOBoard::getDataStream( QFile& file, QIODevice::OpenModeFlag mode )
{
    file.open( mode );
    unique_ptr< QDataStream > stream( new QDataStream( &file ));
    stream->setVersion( QDataStream::Qt_4_6 );
    return stream;
}

/*********************************************************************************/
/*********************************************************************************/

unique_ptr< QDataStream > IOBoard::insertBoardValuesIntoStream( unique_ptr< QDataStream > stream, Board& board )
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

bool IOBoard::checkReadValues( vector< int >& readValues, BoardSize boardSize )
{
    vector< int > valuesToCompare;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        valuesToCompare.push_back( i );
    }

    for ( int value : readValues )
    {
        auto it = std::find( std::begin( valuesToCompare ), std::end( valuesToCompare ), value );

        if ( it == std::end( valuesToCompare ))
        {
            return false;
        }

        valuesToCompare.erase( it );
    }
    return true;
}

