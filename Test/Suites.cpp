
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
    test.testCreateGraphicBoard( GRAPH_FIVE_50_SCALED );
    test.testCreateGraphicBoard( GRAPH_SIX_75_CROPPED );
}


QTEST_APPLESS_MAIN(TestFifteen)

#include "Suites.moc"

