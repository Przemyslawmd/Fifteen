
#ifndef FIFTEEN_CONTROLLER_H
#define FIFTEEN_CONTROLLER_H

#include "FileBoard/IOBoard.h"
#include "GraphicBoard/ImageProvider.h"
#include "Types.h"
#include "UndoMove.h"

#include <QImage>

#include <memory>
#include <vector>


class Controller
{
public:

    Controller();
    Controller( const Controller& ) = delete;
    Controller operator=( const Controller& ) = delete;

    bool loadGraphic( QImage& );
    void removeGraphic();
    bool isGraphic( BoardSize );

    TileSize getTileSize( BoardSize );
    std::vector< std::unique_ptr< QImage >>& getImages( BoardSize );

    void writeBoardIntoFile( Board&, const std::string& file );
    std::unique_ptr< std::vector< uint >> readBoardFromFile( const std::string& file );

    void putMove( Move move, uint row, uint col );
    uint getUndoMove();
    void resetUndoMove();

private:

    std::unique_ptr< ImageProvider > imageProvider;
    std::unique_ptr< UndoMove > undoMoveService;
};

#endif

