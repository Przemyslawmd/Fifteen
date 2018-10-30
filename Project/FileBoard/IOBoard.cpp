
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

    int integerFromStream;
    stream >> integerFromStream;
    BoardMode boardMode = static_cast< BoardMode >( integerFromStream );

    if ( boardMode != BoardMode::GRAPHIC && boardMode != BoardMode::NUMERIC )
    {
        Message::putMessage( MessageCode::READ_BOARD_TYPE_ERROR );
        return false;
    }

    stream >> integerFromStream;
    BoardSize boardSize = static_cast< BoardSize >( integerFromStream );

    if ( boardSize < BoardSize::FOUR || boardSize > BoardSize::SEVEN )
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        return false;
    }

    boardNumbers.resize( boardSize * boardSize );
    for ( auto iter = boardNumbers.begin(); iter != boardNumbers.end(); iter++ )
    {
        stream >> *iter;
    }

    if ( checkReadValues( boardNumbers ) == false )
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
    stream << provider.getImageSquareSize( boardSize );
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

bool IOBoard::checkReadValues( vector< int >& readNumbers )
{
    for ( int number = 0; number < readNumbers.size(); number++ )
    {
        if ( std::find( readNumbers.begin(), readNumbers.end(), number ) == readNumbers.end() )
        {
            return false;
        }
    }

    return true;
}

