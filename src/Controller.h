
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

    Controller() = default;
    Controller( const Controller& ) = delete;
    Controller( Controller&& ) = delete;
    Controller& operator=( const Controller& ) = delete;
    Controller& operator=( Controller&& ) = delete;

    Result generateBoard( BoardSize, BoardMode );
    void solveBoard();

    const std::vector<size_t>& getValues() const;
    size_t getEmptyTile() const;
    BoardMode getBoardMode() const;

    std::tuple<size_t, size_t> getBoardAttributes() const;
    size_t getFontSize() const;

    std::tuple<Move, size_t, size_t> makeMove( uint tilePosition );
    std::tuple<Move, size_t, size_t> undoMove();

    bool loadGraphic( QImage& );
    bool removeGraphic();

    const std::vector<QImage>& getImages() const;

    void writeBoardIntoFile( const std::string& file );
    bool readBoardFromFile( const std::string& file );

private:

    bool isGraphic( BoardSize );

    std::unique_ptr<Board> board{ std::make_unique<Board>( BoardSize::FOUR, BoardMode::NUMERIC ) };
    std::unique_ptr<ImageProvider> imageProvider;
    std::unique_ptr<UndoMove> undoMoveService{ std::make_unique<UndoMove>() };
};

#endif

