
#include "IODataModel.h"
#include "MappedValues.h"
#include "GraphicBoard/ImageProvider.h"

IODataModel::IODataModel() {}

IODataModel::IODataModel( Board& board, BoardMode mode )
{
    boardSize = board.getSize();
    values = &board.sendBoard();

    boardMode = mode;
    if ( boardMode == BoardMode::NUMERIC )
    {
        return;
    }

    ImageProvider& imageProvider = ImageProvider::getInstance();
    images = &imageProvider.getImages( boardSize );
    tileSize = imageProvider.getTileSize( boardSize );
    tileImageBytes = images->at( 0 )->byteCount();
}

/*********************************************************************************/
/*********************************************************************************/

IODataModel::~IODataModel()
{
    delete imagesData;
    imagesData = nullptr;
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

    for ( QImage* image : *images )
    {
        stream.writeRawData( reinterpret_cast< const char* >( image->bits() ), tileImageBytes );
    }
}

/*********************************************************************************/
/*********************************************************************************/

Result IODataModel::readDataFromStream( QDataStream& stream )
{
    int boardModeInt;
    stream >> boardModeInt;
    if ( boardModeInt != 0 && boardModeInt != 1 )
    {
        return Result::READ_BOARD_TYPE_ERROR;
    }
    boardMode = static_cast< BoardMode >( boardModeInt );

    uint boardSizeInt;
    stream >> boardSizeInt;
    if ( boardSizeInt < 4 || boardSizeInt > 7 )
    {
        return  Result::READ_BOARD_SIZE_ERROR;
    }
    boardSize = Mapped::getBoardSizeByInt( boardSizeInt );

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
    if ( tileSizeInt != 50 && tileSizeInt != 75 && tileSizeInt != 100 && tileSizeInt != 125 && tileSizeInt != 150 )
    {
        return Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR;
    }
    tileSize = Mapped::getTileSizeByInt( tileSizeInt );

    stream >> tileImageBytes;
    imagesData = new uchar[tilesCount * tileImageBytes];
    if ( stream.readRawData( (char*) imagesData, tilesCount * tileImageBytes ) == -1 )
    {
        return Result::READ_BOARD_IMAGES_DATA_ERROR;
    }

    return Result::OK;
}

