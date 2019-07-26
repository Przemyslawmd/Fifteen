
#include "IOBoard.h"
#include "IODataModel.h"
#include "IOFile.h"
#include "../MappedValues.h"
#include "../Options.h"
#include "../Message.h"
#include "../GraphicBoard/ImageProvider.h"
#include <memory>

using std::unique_ptr;

IOBoard::IOBoard(){}

/*********************************************************************************/
/*********************************************************************************/

void IOBoard::writeBoardIntoFile( Board& board, BoardMode boardMode, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel( board, boardMode );
    dataModel.writeDataIntoStream( stream );
}

/*********************************************************************************/
/*********************************************************************************/

Result IOBoard::readBoardFromFile( const QString& fileName, vector< uint >& boardNumbers )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    int integerFromStream;
    stream >> integerFromStream;
    BoardMode boardMode = static_cast< BoardMode >( integerFromStream );

    if ( boardMode != BoardMode::GRAPHIC && boardMode != BoardMode::NUMERIC )
    {
        return Result::READ_BOARD_TYPE_ERROR;
    }

    uint boardSizeInt;
    stream >> boardSizeInt;

    if ( boardSizeInt < 4 || boardSizeInt > 7 )
    {
        return  Result::READ_BOARD_SIZE_ERROR;
    }

    boardNumbers.resize( boardSizeInt * boardSizeInt );
    for ( auto iter = boardNumbers.begin(); iter != boardNumbers.end(); iter++ )
    {
        stream >> *iter;
    }

    if ( checkReadValues( boardNumbers ) == false )
    {
        return Result::READ_BOARD_VALUES_ERROR;
    }

    if ( boardMode == BoardMode::GRAPHIC )
    {
        ImageProvider& imageProvider = ImageProvider::getInstance();
        BoardSize boardSize = Mapped::getBoardSizeByInt( boardSizeInt );
        Result result = imageProvider.restoreGraphicBoardFromFile( stream, boardSize );
        if ( result != Result::OK )
        {
            return result;
        }
    }

    Options::boardMode = boardMode;
    boardNumbers.push_back( boardSizeInt );
    return Result::OK;
}

/*********************************************************************************/
/* PRIVATE ***********************************************************************/

bool IOBoard::checkReadValues( vector< uint >& readNumbers )
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

