
#include "IODataModel.h"
#include "../MappedValues.h"
#include "../GraphicBoard/ImageProvider.h"

IODataModel::IODataModel() {}

IODataModel::IODataModel( Board& board, BoardMode mode )
{
    boardSize = board.getSize();
    values = &board.sendBoard();

    if ( boardMode = mode; boardMode == BoardMode::NUMERIC )
    {
        return;
    }

    ImageProvider& imageProvider = ImageProvider::getInstance();
    images = &imageProvider.getImages( boardSize );
    tileSize = imageProvider.getTileSize( boardSize );
    tileImageBytes = images->at( 0 ).get()->sizeInBytes();
}

/*********************************************************************************/
/*********************************************************************************/

void IODataModel::writeDataIntoStream( QDataStream& stream )
{
    stream << static_cast< int >( boardMode );
    stream << Mapped::boardSizeInt.at( boardSize );

    for ( uint number : *values )
    {
        stream << number;
    }

    if ( boardMode == BoardMode::NUMERIC )
    {
        return;
    }

    stream << Mapped::tileSizeInt.at( tileSize );
    stream << tileImageBytes;

    for ( auto& image : *images )
    {
        stream.writeRawData( reinterpret_cast< const char* >( image.get()->bits() ), tileImageBytes );
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
        boardSize = Mapped::getBoardSizeByInt( boardSizeInt );
    }
    catch (...)
    {
        return  Result::READ_BOARD_SIZE_ERROR;
    }

    uint tilesCount = boardSizeInt * boardSizeInt;
    values = new vector< uint >( tilesCount );
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

    if ( boardMode == BoardMode::NUMERIC )
    {
        return Result::OK;
    }

    uint tileSizeInt;
    stream >> tileSizeInt;
    try
    {
        tileSize = Mapped::getTileSizeByInt( tileSizeInt );
    }
    catch (...)
    {
        return Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR;
    }

    stream >> tileImageBytes;
    uint imagesDataBytes = tilesCount * tileImageBytes;
    imagesData = new uchar[imagesDataBytes];
    if ( stream.readRawData( reinterpret_cast< char* >( imagesData ), imagesDataBytes ) != imagesDataBytes )
    {
        return Result::READ_BOARD_IMAGES_DATA_ERROR;
    }

    return Result::OK;
}

