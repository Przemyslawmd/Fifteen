
#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include <memory>
#include <vector>

#include <QImage>

#include "../Types.h"


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

    void createTilesFromImage( QImage&, BoardSize, uint tileSize, GraphicMode );
    void createTiles( QImage&, uint boardSize, uint tileSize );
    std::vector<QImage>& getImages();

    TileSize tileSize;
    FontSize fontSize;
    std::vector<QImage> images;
};

#endif

