
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

    IODataModel( Board&, BoardMode );

    void writeDataIntoStream( QDataStream& );

private:

    uint boardSize;
    uint boardMode;
    uint tileSize;
    uint bytesForImage;
    vector< uint >* values;
    vector< QImage* >* images;
    char* imagesData;
};

#endif // IODATAMODEL_H

