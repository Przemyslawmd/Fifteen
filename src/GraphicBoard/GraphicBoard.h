
#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include "../Types.h"

#include <QImage>

#include <memory>
#include <vector>

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
    std::vector< std::unique_ptr< QImage >>& getImages();

    TileSize tileSize;
    FontSize fontSize;
    std::vector< std::unique_ptr< QImage >> images;
};

#endif

