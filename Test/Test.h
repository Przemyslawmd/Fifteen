
#ifndef TEST_H
#define TEST_H

#include "../Project/Board.h"
#include <QImage>

class Test
{
public:

    void testCreateBoardSolved( BoardSize );
    void testCreateBoardRandom( BoardSize );
    void testCreateBoardRandomWithChange( BoardSize, BoardSize );
    void testMoveSquareDefined( vector< int >& moves, vector< uint >& expectedTiles, BoardSize );
    void testSaveAndLoadBoard( vector< int >& moves, vector< uint >& expectedTiles, BoardSize );
    void testCreateGraphicBoard( int testNumber );

private:

    void checkTiles( uint boardSize, vector< uint >& values );
    void compareQImage( const QImage&, const QImage& );
};

#endif // TEST_H

