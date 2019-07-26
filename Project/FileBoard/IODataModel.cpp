
#include "IODataModel.h"
#include "MappedValues.h"
#include "GraphicBoard/ImageProvider.h"

IODataModel::IODataModel() {}

IODataModel::IODataModel( Board& board, BoardMode mode )
{
    BoardSize size = board.getSize();
    boardSize = Mapped::boardSizeInt.at( size );
    values = &board.sendBoard();

    boardMode = mode == BoardMode::NUMERIC ? 0 : 1;

    if ( boardMode == 0 )
    {
        return;
    }

    ImageProvider& imageProvider = ImageProvider::getInstance();
    images = &imageProvider.getImages( size );
    tileSize = Mapped::tileSizeInt.at( imageProvider.getTileSize( size ));
    bytesForImage = images->at( 0 )->byteCount();
}

/*********************************************************************************/
/*********************************************************************************/

void IODataModel::writeDataIntoStream( QDataStream& stream )
{
    stream << boardMode;
    stream << boardSize;

    for ( uint number : *values )
    {
        stream << number;
    }

    if ( boardMode == 0 )
    {
        return;
    }

    stream << tileSize;
    stream << bytesForImage;

    for ( QImage* image : *images )
    {
        stream.writeRawData( reinterpret_cast< const char* >( image->bits() ), bytesForImage );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void IODataModel::readDataFromStream( QDataStream& stream )
{
    stream >> boardMode;
    stream >> boardSize;

    values = new vector< uint >( boardSize * boardSize );
    for ( auto iter = values->begin(); iter != values->end(); iter++ )
    {
        stream >> *iter;
    }

    if ( boardMode == 0 )
    {
        return;
    }

    stream >> tileSize;
    stream >> bytesForImage;
}

/*********************************************************************************/
/*********************************************************************************/

Result IODataModel::validateData()
{
    if ( boardMode != 0 && boardMode != 1 )
    {
        return Result::READ_BOARD_TYPE_ERROR;
    }

    if ( boardSize < 4 || boardSize > 7 )
    {
        return  Result::READ_BOARD_SIZE_ERROR;
    }

    for ( uint number = 0; number < values->size(); number++ )
    {
        if ( std::find( values->begin(), values->end(), number ) == values->end() )
        {
            return Result::READ_BOARD_VALUES_ERROR;
        }
    }

    if ( boardMode == 0 )
    {
        return Result::OK;
    }

    if ( tileSize != 50 && tileSize != 75 && tileSize != 100 && tileSize != 125 && tileSize != 150 )
    {
        return Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR;
    }

    return Result::OK;
}

