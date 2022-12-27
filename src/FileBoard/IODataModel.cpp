
#include "IODataModel.h"
#include "../MappedValues.h"
#include "../GraphicBoard/ImageProvider.h"

using std::make_unique;
using std::unique_ptr;
using std::vector;


IODataModel::IODataModel( Board& board, BoardMode mode )
{
    boardSize = board.getSize();
    values = make_unique< vector< uint >>( board.sendBoard() );

    if ( boardMode = mode; boardMode == BoardMode::NUMERIC )
    {
        return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

void IODataModel::writeDataIntoStream( QDataStream& stream )
{
    stream << static_cast< int >( boardMode );
    stream << Maps::boardSizeInt.at( boardSize );

    for ( uint number : *values )
    {
        stream << number;
    }

    if ( boardMode == BoardMode::NUMERIC )
    {
        return;
    }
}

/*********************************************************************************/
/*********************************************************************************/

Result IODataModel::readDataFromStream( QDataStream& stream )
{
    int boardModeInt;
    if ( stream >> boardModeInt; boardModeInt != 0 && boardModeInt != 1 )
    {
        return Result::READ_BOARD_TYPE_ERROR;
    }
    boardMode = static_cast< BoardMode >( boardModeInt );

    uint boardSizeInt;
    stream >> boardSizeInt;
    try
    {
        boardSize = Maps::getBoardSizeByInt( boardSizeInt );
    }
    catch (...)
    {
        return  Result::READ_BOARD_SIZE_ERROR;
    }

    uint tilesCount = boardSizeInt * boardSizeInt;
    values = make_unique< vector< uint >>( tilesCount );
    for ( auto iter = values->begin(); iter != values->end(); iter++ )
    {
        stream >> *iter;
    }

    for ( uint number = 0; number < values->size(); number++ )
    {
        if ( std::find( values->begin(), values->end(), number ) == values->end() )
        {
            return Result::READ_BOARD_VALUES_ERROR;
        }
    }

    return Result::OK;
}

