
#include "Test.h"
#include <QtTest>


void Test::testCreateBoardSolved( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->sendBoard();

    for ( int i = 0; i < size * size - 1; i++)
    {
        QCOMPARE( values[i], i + 1 );
    }

    QCOMPARE( values[size * size - 1], 0 );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandom( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->randomBoard();
    checkSquares( size, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandomWithChange( BoardSize firstSize, BoardSize secondSize )
{
    Board* board = Board::createBoard( firstSize );
    board->randomBoard();
    board->randomBoard();
    vector< int >& values = board->randomBoard();

    checkSquares( firstSize, values );

    board = Board::createBoard( secondSize );
    board->randomBoard();
    values = board->randomBoard();

    checkSquares( secondSize, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::checkSquares( BoardSize boardSize, vector< int >& squares )
{
    QList< int > values;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        values.append( i );
    }

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        QCOMPARE( values.contains( squares[i] ), true );
        values.removeOne( squares[i] );
    }

    // List should be empty at the end
    QCOMPARE( values.size(), 0 );
}

