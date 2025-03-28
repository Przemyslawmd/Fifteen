
#ifndef FIFTEEN_GRAPHIC_BOARD_H
#define FIFTEEN_GRAPHIC_BOARD_H

#include <memory>
#include <vector>

#include <QImage>

#include "Types.h"


class GraphicBoard
{
public:

    GraphicBoard() = default;
    GraphicBoard( const GraphicBoard& ) = delete;
    GraphicBoard( GraphicBoard&& ) = delete;
    GraphicBoard& operator=( const GraphicBoard& ) = delete;
    GraphicBoard& operator=( GraphicBoard&& ) = delete;

private:

    friend class ImageProvider;

    void createTilesFromImage( QImage&, BoardSize, size_t tileSize, GraphicMode );
    void createTiles( QImage&, size_t boardSize, size_t tileSize );
    const std::vector<QImage>& getImages() const;

    TileSize tileSize;
    FontSize fontSize;
    std::vector<QImage> images;
};

#endif

