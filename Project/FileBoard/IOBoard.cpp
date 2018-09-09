
#include "IOBoard.h"
#include "../Options.h"
#include "../Message.h"
#include "../GraphicBoard/ImageProvider.h"
#include "IOFile.h"

IOBoard::IOBoard(){}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveNumericBoardInFile( Board& board, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    stream << static_cast< int >( BoardMode::NUMERIC );
    stream << board.getCurrentSize();
    insertBoardValuesIntoStream( stream, board );
}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveGraphicBoardInFile( Board& board, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    stream << static_cast< int >( BoardMode::GRAPHIC );
    BoardSize boardSize = board.getCurrentSize();
    stream << static_cast< int >( boardSize );

    insertBoardValuesIntoStream( stream, board );
    insertBoardPicturesIntoStream( stream, boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::readBoardFromFile( QString fileName, vector< int >& values )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    int boardModeInt;
    stream >> boardModeInt;
    BoardMode boardMode = static_cast< BoardMode >( boardModeInt );

    if ( boardMode != BoardMode::GRAPHIC && boardMode != BoardMode::NUMERIC )
    {
        Message::putMessage( MessageCode::READ_BOARD_TYPE_ERROR );
        return false;
    }

    int boardSizeInt;
    stream >> boardSizeInt;
    BoardSize boardSize = static_cast< BoardSize >( boardSizeInt );

    if ( boardSize < BoardSize::FOUR || boardSize > BoardSize::SEVEN )
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        return false;
    }

    int squareCount = boardSize * boardSize;
    values.resize( squareCount );

    for ( int i = 0; i < squareCount ; i++ )
    {
        stream >> values.at( i );
    }

    if ( checkReadValues( values, squareCount ) == false )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
        return false;
    }

    Options::setBoardMode( boardMode );

    if ( boardMode == BoardMode::GRAPHIC )
    {
        ImageProvider& imageProvider = ImageProvider::getInstance();
        if ( imageProvider.restoreGraphicBoardFromFile( stream, boardSize ) == false )
        {
            return false;
        }
    }

    values.push_back( boardSize );
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

void IOBoard::insertBoardPicturesIntoStream( QDataStream& stream, BoardSize boardSize)
{
    ImageProvider& provider = ImageProvider::getInstance();
    stream << static_cast< int >( provider.getImageSquareSize() );
    vector< QImage* >& pictures = provider.getImages( boardSize );
    int byteCount = pictures.at( 0 )->byteCount();
    stream << byteCount;

    for ( auto iter = pictures.begin(); iter != pictures.end(); iter++ )
    {
        stream.writeRawData( (char*) (*iter)->bits(), byteCount );
    }
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::checkReadValues( vector< int >& readValues, int squareCount )
{
    vector< int > valuesToCompare( squareCount );

    for ( int i = 0; i < squareCount; i++ )
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

