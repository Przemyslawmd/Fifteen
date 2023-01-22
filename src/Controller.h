
#ifndef FIFTEEN_CONTROLLER_H
#define FIFTEEN_CONTROLLER_H

#include "Board.h"
#include "FileBoard/IOBoard.h"
#include "GraphicBoard/ImageProvider.h"
#include "Types.h"
#include "UndoMove.h"

#include <QImage>

#include <memory>
#include <tuple>
#include <vector>


class Controller
{
public:

    Controller();
    Controller( const Controller& ) = delete;
    Controller operator=( const Controller& ) = delete;

    bool generateBoard( BoardSize, BoardMode );
    void solveBoard();
    Board& getBoard();
    std::tuple< uint, uint > getBoardAttributes();

    bool loadGraphic( QImage& );
    bool removeGraphic();
    bool isGraphic( BoardSize );

    TileSize getTileSize( BoardSize );
    std::vector< std::unique_ptr< QImage >>& getImages();

    void writeBoardIntoFile( const std::string& file );
    void readBoardFromFile( const std::string& file );

    void putMove( Move move, uint row, uint col );
    uint getUndoMove();

private:

    std::unique_ptr< Board > board;
    std::unique_ptr< ImageProvider > imageProvider;
    std::unique_ptr< UndoMove > undoMoveService;
};

#endif

