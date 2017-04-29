
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
    void testCreateBoardSolved( int boardSize );

    void suiteCreateBoardRandom();
    void testCreateBoardRandom( int boardSize );

    void suiteMoveSquareDefined();
    void testMoveSquareDefined( int boardSize, int dataNumber );
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
}


void TestFifteen::suiteMoveSquareDefined()
{
    testMoveSquareDefined( 4, 1 );
}

/**********************************************/
/* TEST CREATING BOARD SOLVED *****************/
// Test creating board at the beginning
// Board should be created and solved

void TestFifteen::testCreateBoardSolved( int boardSize )
{
    Board* board = Board::createBoard( boardSize );
    int** squares = board->sendBoard();

    int k = 1;

    for ( int i = 0; i < boardSize; i++)
    {
        for ( int j = 0; j < boardSize; j++)
        {
            if ( i != ( boardSize -1 ) || j != ( boardSize - 1 ) )
                QCOMPARE( squares[i][j], k++ );
            else
                QCOMPARE( squares[i][j], 0 );
        }
    }
}

/**********************************************/
/* TEST CREATING BOARD RANDOM *****************/
// Test generating board
// Values are not sorted

void TestFifteen::testCreateBoardRandom( int boardSize )
{
    Board* board = Board::createBoard( boardSize );
    int** squares = board->randomBoard();

    QList<int> values;

    for ( int i = 0; i < ( boardSize * boardSize ); i++ )
        values.append( i );

    for ( int i = 0; i < boardSize; i++)
    {
        for ( int j = 0; j < boardSize; j++)
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

void TestFifteen::testMoveSquareDefined( int boardSize, int dataNumber )
{
    Board* board = Board::createBoard( boardSize );

    int* moves = Data::getMoves( dataNumber );
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
    int* expectedSquares = Data::getExcpectedBoard( dataNumber );

    int k = 0;

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
            QCOMPARE( squares[i][j], expectedSquares[k++] );
    }
}

QTEST_APPLESS_MAIN(TestFifteen)

#include "testfifteen.moc"
