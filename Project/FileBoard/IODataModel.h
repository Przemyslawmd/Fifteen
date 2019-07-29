
#ifndef IODATAMODEL_H
#define IODATAMODEL_H

#include "Board.h"
#include "QImage"
#include "Message.h"
#include <vector>
#include <memory>

using std::vector;

class IODataModel
{
public:

    IODataModel();
    IODataModel( Board&, BoardMode );
    ~IODataModel();

    void writeDataIntoStream( QDataStream& );
    Result readDataFromStream( QDataStream& );

    BoardSize boardSize;
    BoardMode boardMode;
    TileSize tileSize;
    uint tileImageBytes;
    vector< uint >* values;
    vector< QImage* >* images;
    uchar* imagesData;
};

#endif // IODATAMODEL_H

