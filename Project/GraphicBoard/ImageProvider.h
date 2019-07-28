
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../Types.h"
#include "../Message.h"

class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    vector< QImage* >& getImages( BoardSize );
    void prepareGraphicBoard( QImage&, TileSize );
    Result restoreGraphicBoardFromFile( uchar*, BoardSize, uint, uint );
    bool isGraphicBoard( BoardSize );
    TileSize getTileSize( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void createTilesForGraphicBoard( BoardSize, TileSize, QImage& );
    void removeBoard( GraphicBoard*& );

    void ( GraphicBoard::*createImage )( QImage&, BoardSize, TileSize );

    static ImageProvider* instance;
    std::map< BoardSize, GraphicBoard* > images;
};

#endif

