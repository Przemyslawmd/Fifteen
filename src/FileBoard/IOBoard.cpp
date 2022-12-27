
#include "IOBoard.h"
#include "IOFile.h"
#include "../MappedValues.h"
#include "../Options.h"
#include "../GraphicBoard/ImageProvider.h"


void IOBoard::writeBoardIntoFile( Board& board, BoardMode boardMode, const QString& fileName )
{
    IOFile file( fileName, QIODevice::WriteOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel( board, boardMode );
    dataModel.writeDataIntoStream( stream );
}

/*********************************************************************************/
/*********************************************************************************/

std::unique_ptr< std::vector< uint >> IOBoard::readBoardFromFile( const QString& fileName )
{
    IOFile file( fileName, QIODevice::ReadOnly );
    QDataStream& stream = file.getDataStream();

    IODataModel dataModel;
    if ( auto result = dataModel.readDataFromStream( stream ); result != Result::OK )
    {
        Message::putMessage( result );
        return nullptr;
    }

    BoardMode boardMode = static_cast< BoardMode >( dataModel.boardMode );
    std::unique_ptr< std::vector< uint >> boardData = std::move( dataModel.values );

    boardData->push_back( Maps::boardSizeInt.at( dataModel.boardSize ));
    return boardData;
}

