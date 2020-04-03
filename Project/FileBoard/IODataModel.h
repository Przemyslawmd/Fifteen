
#ifndef IODATAMODEL_H
#define IODATAMODEL_H

#include "../Board.h"
#include "QImage"
#include "../Message.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

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
    unique_ptr< vector< uint >> values;
    vector< unique_ptr< QImage >>* images;
    uchar* imagesData;
};

#endif

