
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
    void testMoveSquareDefined( int testNumber );
    void testSaveAndLoadBoard( int testNumber );
    void testCreateGraphicBoard( int testNumber );

private:

    void checkTiles( int boardSize, vector< int >& values );
    void compareQImage( const QImage&, const QImage& );
};

#endif // TEST_H

