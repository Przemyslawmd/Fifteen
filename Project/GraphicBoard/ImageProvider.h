
#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "GraphicBoard.h"
#include "../FileBoard/IODataModel.h"
#include "../Types.h"
#include "../Message.h"

using std::unique_ptr;
using std::map;


class ImageProvider
{
public:

    static ImageProvider& getInstance();
    static void deleteInstance();

    vector< unique_ptr< QImage >>& getImages( BoardSize );

    void prepareGraphicBoard( QImage&, TileSize );
    bool restoreBoardFromFile( IODataModel& );
    bool isGraphicBoard( BoardSize );
    TileSize getTileSize( BoardSize );

private:

    ImageProvider();
    ~ImageProvider();

    bool checkImageSize( QImage&, BoardSize, TileSize ) ;
    void createTilesForGraphicBoard( BoardSize, TileSize, QImage& );
    void removeBoard( GraphicBoard*& );

    static ImageProvider* instance;
    map< BoardSize, GraphicBoard* > images;
};

#endif

