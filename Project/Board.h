
#ifndef BOARD_H
#define BOARD_H

#include "Types.h"
#include <QList>
#include <QTime>
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Board
{
public:

    static Board* board;
    static Board* createBoard( BoardSize );
    static Board* createBoard( vector< int >& values, BoardSize );

    Move checkMove( int row, int col );

    BoardSize getSize();
    vector< int >& sendBoard();
    vector< int >& randomBoard();
    void solveBoard();

private:

    BoardSize boardSize;
    vector< int > values;
    const int EMPTY_SQUARE = 0;

    Board( BoardSize );
    Board( vector< int >& values, BoardSize );

    void makeMove( int srcRow, int srcColumn, int dstRow, int dstColumn );
    int findEmptyTill();
};

#endif // BOARD_H
