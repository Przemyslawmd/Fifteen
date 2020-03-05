
#ifndef IODATAMODEL_H
#define IODATAMODEL_H

#include "../Board.h"
#include "QImage"
#include "../Message.h"
#include <vector>
#include <memory>

using std::vector;

class IODataModel
{
public:

    IODataModel();
    IODataModel( Board&, BoardMode );

    void writeDataIntoStream( QDataStream& );
    Result readDataFromStream( QDataStream& );

    BoardSize boardSize;
    BoardMode boardMode;
    TileSize tileSize;
    uint tileImageBytes;
    vector< uint >* values;
    vector< std::unique_ptr< QImage >>* images;
    uchar* imagesData;
};

#endif

