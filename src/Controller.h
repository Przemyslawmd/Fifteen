
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
    Controller( Controller&& ) = delete;
    Controller& operator=( const Controller& ) = delete;
    Controller& operator=( Controller&& ) = delete;

    Result generateBoard( BoardSize, BoardMode );
    void solveBoard();

    std::vector< uint >& getValues();
    uint getNullValue();
    BoardMode getBoardMode();

    std::tuple< uint, uint > getBoardAttributes();
    uint getFontSize();

    std::tuple< Move, uint, uint > makeMove( uint tilePosition );
    std::tuple< Move, uint, uint > undoMove();

    bool loadGraphic( QImage& );
    bool removeGraphic();

    std::vector< std::unique_ptr< QImage >>& getImages();

    void writeBoardIntoFile( const std::string& file );
    bool readBoardFromFile( const std::string& file );

private:

    bool isGraphic( BoardSize );

    std::unique_ptr< Board > board;
    std::unique_ptr< ImageProvider > imageProvider;
    std::unique_ptr< UndoMove > undoMoveService;
};

#endif

