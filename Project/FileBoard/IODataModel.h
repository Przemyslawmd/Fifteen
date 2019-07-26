
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
    void readDataFromStream( QDataStream& );
    Result validateData();

    uint boardSize;
    uint boardMode;
    uint tileSize;
    uint bytesForImage;
    vector< uint >* values;
    vector< QImage* >* images;
    char* imagesData;
};

#endif // IODATAMODEL_H

