
#include <QString>
#include <QtTest>

#include "../Project/Board.h"
#include "Test.h"

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:   

    void suiteCreateBoardSolved();
    void suiteCreateBoardRandom();
    void suiteMoveSquareDefined();
    void suiteSaveAndLoadBoard();
    void suiteCreateGraphicBoard();
    void suiteUndoMoves();
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
    test.testMoveSquareDefined( 0 );
    test.testMoveSquareDefined( 1 );
}


void TestFifteen::suiteSaveAndLoadBoard()
{
    Test test;
    test.testSaveAndLoadBoard( 0 );
    test.testSaveAndLoadBoard( 1 );
}


void TestFifteen::suiteCreateGraphicBoard()
{
    Test test;

    // BoardSize: 5; SquareSize: 50, GraphicMode: Scalled
    test.testCreateGraphicBoard( 0 );

    // BoardSize: 6; SquareSize: 75, GraphicMode: Cropped
    test.testCreateGraphicBoard( 1 );
}


void TestFifteen::suiteUndoMoves()
{
}

QTEST_APPLESS_MAIN(TestFifteen)

#include "Suites.moc"

