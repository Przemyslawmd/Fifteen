
#include <QString>
#include <QtTest>

#include "../Project/Board.h"
#include "../Project/Board.cpp"
#include "Data.h"

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:   

    void suiteCreateBoardSolved();
    void suiteCreateBoardRandom();
    void suiteMoveSquareDefined();
    void suiteSaveAndLoadBoard();


    void testCreateBoardSolved( int boardSize );
    void testCreateBoardRandom( int boardSize );
    void testCreateBoardRandomWithChange( int boardSizeFirst, int boardSizeSecond );
    void testMoveSquareDefined( int boardSize, int testNumber );
    void testSaveAndLoadBoard();

    void checkSquares( int boardSize, int** squares );
};


void TestFifteen::suiteCreateBoardSolved()
{
    testCreateBoardSolved( 4 );
    testCreateBoardSolved( 6 );
}


void TestFifteen::suiteCreateBoardRandom()
{
    testCreateBoardRandom( 5 );
    testCreateBoardRandom( 7 );
    testCreateBoardRandomWithChange( 5, 6 );
    testCreateBoardRandomWithChange( 7, 4 );
}


void TestFifteen::suiteMoveSquareDefined()
{
    testMoveSquareDefined( 4, 0 );
    testMoveSquareDefined( 5, 1 );
}


void TestFifteen::suiteSaveAndLoadBoard()
{
    testSaveAndLoadBoard();
    testSaveAndLoadBoard();

}

/*********************************************************************************/
/* TEST CREATE BOARD *************************************************************/
// Test creating initial state of a board, values in a board should be sorted

void TestFifteen::testCreateBoardSolved( int boardSize )
{
    Board* board = Board::createBoard( boardSize );
    int** squares = board->sendBoard();

    for ( int i = 0, k = 1; i < boardSize; i++)
    {
        for ( int j = 0; j < boardSize; j++)
        {
            if ( i != ( boardSize - 1 ) || j != ( boardSize - 1 ) )
                QCOMPARE( squares[i][j], k++ );
            else
                QCOMPARE( squares[i][j], 0 );
        }
    }
}

/*********************************************************************************/
/* TEST RANDOM BOARD *************************************************************/
// After random board check whether a board has all values

void TestFifteen::testCreateBoardRandom( int boardSize )
{
    Board* board = Board::createBoard( boardSize );
    int** squares = board->randomBoard();
    checkSquares( boardSize, squares );
}

/*********************************************************************************/
/* TEST BOARD WITH CHANGE OF SIZE  ***********************************************/

void TestFifteen::testCreateBoardRandomWithChange( int boardSizeFirst, int boardSizeSecond )
{
    Board* board = Board::createBoard( boardSizeFirst );
    board->randomBoard();
    board->randomBoard();
    int** squares = board->randomBoard();

    checkSquares( boardSizeFirst, squares );

    board = Board::createBoard( boardSizeSecond );
    board->randomBoard();
    squares = board->randomBoard();

    checkSquares( boardSizeSecond, squares );
}

/**************************************************/
/* CHECK SQUARES **********************************/
// Helper method to check whether a board has all square values

void TestFifteen::checkSquares( int boardSize, int** squares )
{
    QList<int> values;

    for ( int i = 0; i < ( boardSize * boardSize ); i++ )
        values.append( i );

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            // Check whether value exists in a list
            QCOMPARE( values.contains( squares[i][j]), true );
            values.removeOne( squares[i][j] );
        }
    }

    // List should be empty at the end
    QCOMPARE( values.size(), 0 );
}

/*************************************************/
/* TEST MOVING SQUARE DEFINED ********************/

void TestFifteen::testMoveSquareDefined( int boardSize, int testNumber )
{
    Board* board = Board::createBoard( boardSize );

    vector< int > moves = Data::getMoves( testNumber );
    int rowNumber;
    int colNumber;

    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        rowNumber = moves[i] / 10;
        colNumber = moves[i] % 10;
        board->checkMove( rowNumber, colNumber );
    }

    int** squares  = board->sendBoard();
    vector< int > expectedSquares = Data::getExpectedSquares( testNumber );

    int k = 0;

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
            QCOMPARE( squares[i][j], expectedSquares[k++] );
    }
}

void TestFifteen::testSaveAndLoadBoard()
{

}

QTEST_APPLESS_MAIN(TestFifteen)

#include "testfifteen.moc"

