
#ifndef GRAPHIC_BOARD_H
#define GRAPHIC_BOARD_H

#include "../FileBoard/IODataModel.h"
#include "../Types.h"
#include <QImage>
#include <vector>

using std::vector;
using std::unique_ptr;

class GraphicBoard
{
public:

    GraphicBoard() = default;
    GraphicBoard( const GraphicBoard& ) = delete;
    GraphicBoard operator=( const GraphicBoard& ) = delete;

private:

    friend class ImageProvider;

    void createTilesFromImage( QImage&, BoardSize, TileSize, GraphicMode );
    void createTiles( QImage*, uint boardSize, uint tileSize );
    bool restoreImagesFromFile( IODataModel& );
    vector< unique_ptr< QImage >>& getImages();

    TileSize tileSize;
    vector< unique_ptr< QImage >> images;
};

#endif

