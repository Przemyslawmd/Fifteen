
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

vector< uint >* IOBoard::readBoardFromFile( const QString& fileName )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel;
    Result result = dataModel.readDataFromStream( stream );
    if ( result != Result::OK )
    {
        Message::putMessage( result );
        return nullptr;
    }

    BoardMode boardMode = static_cast< BoardMode >( dataModel.boardMode );
    uint boardSizeInt = dataModel.boardSize;
    vector< uint >* boardNumbers = dataModel.values;

    if ( boardMode == BoardMode::GRAPHIC )
    {
        ImageProvider& imageProvider = ImageProvider::getInstance();
        BoardSize boardSize = Mapped::getBoardSizeByInt( boardSizeInt );
        Result result = imageProvider.restoreGraphicBoardFromFile( dataModel.imagesData, boardSize, dataModel.tileSize, dataModel.tileImageBytes );
        if ( result != Result::OK )
        {
            Message::putMessage( result );
            return nullptr;
        }
    }

    Options::boardMode = boardMode;
    boardNumbers->push_back( boardSizeInt );
    return boardNumbers;
}

