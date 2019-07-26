
#include "IODataModel.h"
#include "MappedValues.h"
#include "GraphicBoard/ImageProvider.h"

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
