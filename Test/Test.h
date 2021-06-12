
#ifndef TEST_H
#define TEST_H

#include "DataGraphic.h"
#include "../Project/Board.h"
#include "../Project/Message.h"
#include <QImage>

class Test
{
public:

    void testCreateBoardSolved( BoardSize );
    void testCreateBoardRandom( BoardSize );
    void testCreateBoardRandomWithChange( BoardSize, BoardSize );
    void testMoveSquareDefined( std::vector< int >& moves, std::vector< uint >& expectedTiles, BoardSize );
    void testSaveAndLoadBoard( std::vector< int >& moves, std::vector< uint >& expectedTiles, BoardSize );
    void testLoadImproperBoard( QString fileName, Result );
    void testLoadGraphicBoard( QString fileName, Result, BoardSize, TileSize );
    void testCreateGraphicBoard( DataGraphic& );

private:

    void checkTiles( uint boardSize, std::vector< uint >& values );
    void compareQImage( const QImage&, const QImage& );
};

#endif // TEST_H

