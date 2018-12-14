
#include "IOBoard.h"
#include "../MappedValues.h"
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
    stream << Mapped::boardSizeInt.at( board.getSize() );
    insertBoardValuesIntoStream( stream, board );
}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::saveGraphicBoardInFile( Board& board, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    stream << static_cast< int >( BoardMode::GRAPHIC );
    BoardSize boardSize = board.getSize();
    stream << Mapped::boardSizeInt.at( boardSize );

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

    int boardSizeInt;
    stream >> boardSizeInt;

    if ( boardSizeInt < 4 || boardSizeInt > 7 )
    {
        Message::putMessage( MessageCode::READ_BOARD_SIZE_ERROR );
        return false;
    }

    boardNumbers.resize( boardSizeInt * boardSizeInt );
    for ( auto iter = boardNumbers.begin(); iter != boardNumbers.end(); iter++ )
    {
        stream >> *iter;
    }

    if ( checkReadValues( boardNumbers ) == false )
    {
        Message::putMessage( MessageCode::READ_BOARD_VALUES_ERROR );
        return false;
    }

    BoardSize boardSize = Mapped::getBoardSizeByInt( boardSizeInt );

    if ( boardMode == BoardMode::GRAPHIC )
    {
        ImageProvider& imageProvider = ImageProvider::getInstance();
        if ( imageProvider.restoreGraphicBoardFromFile( stream, boardSize ) == false )
        {
            return false;
        }
    }

    Options::setBoardMode( boardMode );
    boardNumbers.push_back( boardSizeInt );
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
    TileSize tileSize = provider.getTileSize( boardSize );
    stream << Mapped::tileSizeInt.at( tileSize );

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
    for ( uint number = 0; number < readNumbers.size(); number++ )
    {
        if ( std::find( readNumbers.begin(), readNumbers.end(), number ) == readNumbers.end() )
        {
            return false;
        }
    }

    return true;
}

