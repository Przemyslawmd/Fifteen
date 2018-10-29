
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
    stream << boardSize;

    insertBoardValuesIntoStream( stream, board );
    insertBoardPicturesIntoStream( stream, boardSize );
}

/*********************************************************************************/
/*********************************************************************************/

bool IOBoard::readBoardFromFile( const QString& fileName, vector< int >& boardNumbers )
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
    boardNumbers.resize( squareCount );

    for ( int number : boardNumbers )
    {
        stream >> number;
    }

    if ( checkReadValues( boardNumbers, squareCount ) == false )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
        return false;
    }

    if ( boardMode == BoardMode::GRAPHIC )
    {
        ImageProvider& imageProvider = ImageProvider::getInstance();
        if ( imageProvider.restoreGraphicBoardFromFile( stream, boardSize ) == false )
        {
            return false;
        }
    }

    Options::setBoardMode( boardMode );
    boardNumbers.push_back( boardSize );
    return true;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

void IOBoard::insertBoardValuesIntoStream( QDataStream& stream, Board& board )
{
    vector< int >& boardNumbers = board.sendBoard();

    for ( int number : boardNumbers )
    {
        stream << number;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::insertBoardPicturesIntoStream( QDataStream& stream, BoardSize boardSize)
{
    ImageProvider& provider = ImageProvider::getInstance();
    stream << provider.getImageSquareSize();
    vector< QImage* >& boardImages = provider.getImages( boardSize );
    int byteCountPerImage = boardImages.at( 0 )->byteCount();
    stream << byteCountPerImage;

    for ( QImage* image : boardImages )
    {
        stream.writeRawData( (char*) image->bits(), byteCountPerImage );
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
        auto it = std::find( valuesToCompare.begin(), valuesToCompare.end(), value );

        if ( it == valuesToCompare.end() )
        {
            return false;
        }

        valuesToCompare.erase( it );
    }
    return true;
}

