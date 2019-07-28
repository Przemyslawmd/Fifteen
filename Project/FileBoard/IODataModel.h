
#ifndef IODATAMODEL_H
#define IODATAMODEL_H

#include "Board.h"
#include "QImage"
#include "Message.h"
#include <vector>

using std::vector;

class IODataModel
{
public:

    IODataModel();
    IODataModel( Board&, BoardMode );

    void writeDataIntoStream( QDataStream& );
    Result readDataFromStream( QDataStream& );

    uint boardSize;
    uint boardMode;
    uint tileSize;
    uint tileImageBytes;
    vector< uint >* values;
    vector< QImage* >* images;
    uchar* imagesData;
};

#endif // IODATAMODEL_H

