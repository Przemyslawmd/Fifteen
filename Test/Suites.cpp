
#include "Test.h"
#include "Defines.h"

#include "../Project/Board.h"

#include <QString>
#include <QtTest>

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:   

    void suiteCreateBoardSolved();
    void suiteCreateBoardRandom();
    void suiteMoveSquareDefined();
    void suiteSaveAndLoadBoard();
    void suiteCreateGraphicBoard();
};


void TestFifteen::suiteCreateBoardSolved()
{
    Test test;
    test.testCreateBoardSolved( BoardSize::FOUR );
    test.testCreateBoardSolved( BoardSize::SIX );
}


void TestFifteen::suiteCreateBoardRandom()
{
    Test test;
    test.testCreateBoardRandom( BoardSize::FIVE );
    test.testCreateBoardRandom( BoardSize::SEVEN );
    test.testCreateBoardRandomWithChange( BoardSize::FIVE, BoardSize::SIX );
    test.testCreateBoardRandomWithChange( BoardSize::SEVEN, BoardSize::FOUR );
}


void TestFifteen::suiteMoveSquareDefined()
{
    Test test;

    vector< int > moves { 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 };
    vector< uint> expectedTiles { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 };
    test.testMoveSquareDefined( moves, expectedTiles, BoardSize::FOUR );

    moves = { 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 };
    expectedTiles = { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 };
    test.testMoveSquareDefined( moves, expectedTiles, BoardSize::FIVE );
}

void TestFifteen::suiteSaveAndLoadBoard()
{
    Test test;

    vector< int > moves { 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 };
    vector< uint> expectedTiles { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 };
    test.testSaveAndLoadBoard( moves, expectedTiles, BoardSize::FOUR );

    moves = { 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 };
    expectedTiles = { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 };
    test.testSaveAndLoadBoard( moves, expectedTiles, BoardSize::FIVE );
}


void TestFifteen::suiteCreateGraphicBoard()
{
    Test test;
    test.testCreateGraphicBoard( GRAPH_FIVE_50_SCALED );
    test.testCreateGraphicBoard( GRAPH_SIX_75_CROPPED );
}


QTEST_APPLESS_MAIN(TestFifteen)

#include "Suites.moc"

