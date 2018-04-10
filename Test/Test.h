
#ifndef TEST_H
#define TEST_H

#include "../Project/Board.h"

class Test
{
public:

    void testCreateBoardSolved( BoardSize );
    void testCreateBoardRandom( BoardSize );
    void testCreateBoardRandomWithChange( BoardSize first, BoardSize second );

private:

    void checkSquares( BoardSize, vector< int >& values );
};

#endif // TEST_H

