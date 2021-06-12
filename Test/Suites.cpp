
#include "../Project/Board.h"

#include <QString>
#include <QtTest>

#include "Test.h"

using std::vector;


class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:   

    void createBoardSolved_1();
    void createBoardSolved_2();
    void createBoardRandom_1();
    void createBoardRandom_2();
    void createBoardRandomAndChange_1();
    void createBoardRandomAndChange_2();
    void moveTiles_1();
    void moveTiles_2();
    void saveAndLoadBoard_1();
    void saveAndLoadBoard_2();
    void loadImproperBoard_1();
    void loadImproperBoard_2();
    void loadImproperBoard_3();
    void loadImproperBoard_4();
    void loadImproperBoard_5();
    void loadImproperBoard_6();
    void loadGraphicBoard();
    void createGraphicBoard_1();
    void createGraphicBoard_2();
};


void TestFifteen::createBoardSolved_1()
{
    Test test;
    test.testCreateBoardSolved( BoardSize::FOUR );
}

void TestFifteen::createBoardSolved_2()
{
    Test test;
    test.testCreateBoardSolved( BoardSize::SIX );
}

void TestFifteen::createBoardRandom_1()
{
    Test test;
    test.testCreateBoardRandom( BoardSize::FIVE );
}

void TestFifteen::createBoardRandom_2()
{
    Test test;
    test.testCreateBoardRandom( BoardSize::SEVEN );
}

void TestFifteen::createBoardRandomAndChange_1()
{
    Test test;
    test.testCreateBoardRandomWithChange( BoardSize::FIVE, BoardSize::SIX );
}

void TestFifteen::createBoardRandomAndChange_2()
{
    Test test;
    test.testCreateBoardRandomWithChange( BoardSize::SEVEN, BoardSize::FOUR );
}

void TestFifteen::moveTiles_1()
{
    vector< int > moves { 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 };
    vector< uint > expectedTiles { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 };
    Test test;
    test.testMoveSquareDefined( moves, expectedTiles, BoardSize::FOUR );
}

void TestFifteen::moveTiles_2()
{

    vector< int > moves { 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 };
    vector< uint > expectedTiles { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 };
    Test test;
    test.testMoveSquareDefined( moves, expectedTiles, BoardSize::FIVE );
}

void TestFifteen::saveAndLoadBoard_1()
{
    vector< int > moves { 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 };
    vector< uint > expectedTiles { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 };
    Test test;
    test.testSaveAndLoadBoard( moves, expectedTiles, BoardSize::FOUR );
}

void TestFifteen::saveAndLoadBoard_2()
{
    vector< int > moves { 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 };
    vector< uint > expectedTiles { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 };
    Test test;
    test.testSaveAndLoadBoard( moves, expectedTiles, BoardSize::FIVE );
}

void TestFifteen::createGraphicBoard_1()
{
    DataGraphic data { BoardSize::FIVE, TileSize::_50, GraphicMode::SCALED, "Scalled_5_50/", false, true, false, false };
    Test test;
    test.testCreateGraphicBoard( data );
}

void TestFifteen::createGraphicBoard_2()
{
    DataGraphic data { BoardSize::SIX, TileSize::_75, GraphicMode::CROPPED, "Cropped_6_75/", false, false, true, false };
    Test test;
    test.testCreateGraphicBoard( data );
}

void TestFifteen::loadImproperBoard_1()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardSize", Result::READ_BOARD_SIZE_ERROR );
}

void TestFifteen::loadImproperBoard_2()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardMode", Result::READ_BOARD_TYPE_ERROR );
}

void TestFifteen::loadImproperBoard_3()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardValues", Result::READ_BOARD_VALUES_ERROR );
}

void TestFifteen::loadImproperBoard_4()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardNotAllValues", Result::READ_BOARD_VALUES_ERROR );
}

void TestFifteen::loadImproperBoard_5()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardTileSize", Result::READ_BOARD_IMAGES_TILE_SIZE_ERROR );
}

void TestFifteen::loadImproperBoard_6()
{
    Test test;
    test.testLoadImproperBoard( "improperBoardNotAllGraphicData", Result::READ_BOARD_IMAGES_DATA_ERROR );
}

void TestFifteen::loadGraphicBoard()
{
    Test test;
    test.testLoadGraphicBoard( "graphicBoardSize5Tile75", Result::OK, BoardSize::FIVE, TileSize::_75 );
}

QTEST_APPLESS_MAIN(TestFifteen)

#include "Suites.moc"

