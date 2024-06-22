
#ifndef FIFTEEN_CONTROLLER_H
#define FIFTEEN_CONTROLLER_H

#include <memory>
#include <tuple>
#include <vector>

#include <QImage>

#include "Board.h"
#include "FileBoard/IOBoard.h"
#include "GraphicBoard/ImageProvider.h"
#include "Types.h"
#include "UndoMove.h"


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

    std::vector<size_t>& getValues();
    uint getNullValue();
    BoardMode getBoardMode();

    std::tuple<size_t, size_t> getBoardAttributes();
    uint getFontSize();

    std::tuple<Move, size_t, size_t> makeMove( uint tilePosition );
    std::tuple<Move, size_t, size_t> undoMove();

    bool loadGraphic( QImage& );
    bool removeGraphic();

    std::vector<std::unique_ptr<QImage>>& getImages();

    void writeBoardIntoFile( const std::string& file );
    bool readBoardFromFile( const std::string& file );

private:

    bool isGraphic( BoardSize );

    std::unique_ptr<Board> board;
    std::unique_ptr<ImageProvider> imageProvider;
    std::unique_ptr<UndoMove> undoMoveService;
};

#endif

