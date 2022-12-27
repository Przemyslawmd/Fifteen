
#ifndef IODATAMODEL_H
#define IODATAMODEL_H

#include <memory>
#include <vector>
#include "../Board.h"
#include "../Message.h"
#include "QImage"


class IODataModel
{
public:

    IODataModel() = default;
    IODataModel( Board&, BoardMode );
    IODataModel( const IODataModel& ) = delete;

    void writeDataIntoStream( QDataStream& );
    Result readDataFromStream( QDataStream& );

    BoardSize boardSize;
    BoardMode boardMode;
    std::unique_ptr< std::vector< uint >> values;
};

#endif

