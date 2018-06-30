
#include "IOBoard.h"
#include "Options.h"
#include "Message.h"
#include "GraphicBoard/ImageProvider.h"
#include "IOFile.h"

IOBoard::IOBoard(){}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveNumericBoardInFile( Board& board, QString fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    stream << static_cast< int >( BoardMode::NUMERIC );
    stream << board.getCurrentSize();
    insertBoardValuesIntoStream( stream, board );
}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveGraphicBoardInFile( Board& board, QString fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    stream << static_cast< int >( BoardMode::GRAPHIC );
    int boardSize = board.getCurrentSize();
    stream << boardSize;

    insertBoardValuesIntoStream( stream, board );

    ImageProvider& provider = ImageProvider::getInstance();
    stream << static_cast< int >( provider.getImageSquareSize() );
    vector< QImage* >& pictures = provider.getImages( static_cast< BoardSize >( boardSize ));
    int byteCount = pictures.at( 0 )->byteCount();
    stream << byteCount;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        stream.writeRawData( (char*) pictures.at( i )->bits(), byteCount );
    }
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::readBoardFromFile( QString fileName, vector< int >& values )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    int boardMode;
    stream >> boardMode;
    if ( boardMode != static_cast< int >( BoardMode::GRAPHIC ) && boardMode != static_cast< int >( BoardMode::NUMERIC ))
    {
        Message::putMessage( MessageCode::READ_BOARD_TYPE_ERROR );
        return false;
    }

    int level;
    stream >> level;
    if ( level < static_cast< int >( BoardSize::FOUR ) || level > static_cast< int >( BoardSize::SEVEN ))
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        return false;
    }

    values.resize( level * level );

    for ( int i = 0; i < level * level ; i++ )
    {
        stream >> values.at( i );
    }

    if ( checkReadValues( values, static_cast< BoardSize >( level )) == false )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
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

        if ( imageProvider.restoreGraphicBoardFromFile( stream, static_cast< BoardSize >( level )) == false )
        {
            return false;
        }
    }

    values.push_back( level );
    return true;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void IOBoard::insertBoardValuesIntoStream( QDataStream& stream, Board& board )
{
    vector< int >& values = board.sendBoard();

    for ( auto iter = values.begin(); iter != values.end(); iter++ )
    {
        stream << *iter;
    }
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

