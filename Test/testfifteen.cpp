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
    void testCreateBoardSolved( int dimension );

    void suiteCreateBoardRandom();
    void testCreateBoardRandom( int dimension );

    void suiteMoveSquareDefined();
    void testMoveSquareDefined( int dimension, int dataNumber );
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

void TestFifteen::testCreateBoardSolved( int size )
{
    Board board( size );
    int** squares = board.sendBoard();

    int k = 1;

    for ( int i = 0; i < size; i++)
    {
        for ( int j = 0; j < size; j++)
        {
            if ( i != ( size -1 ) || j != ( size - 1 ) )
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

void TestFifteen::testCreateBoardRandom( int size )
{
    Board board( size );
    int** squares = board.randomBoard();

    QList<int> values;

    for ( int i = 0; i < ( size * size ); i++ )
        values.append( i );

    for ( int i = 0; i < size; i++)
    {
        for ( int j = 0; j < size; j++)
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

void TestFifteen::testMoveSquareDefined( int dimension, int dataNumber )
{
    Board board( dimension );

    int* moves = Data::getMoves( dataNumber );
    int rowNumber;
    int colNumber;

    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        rowNumber = moves[i] / 10;
        colNumber = moves[i] % 10;
        board.checkMove( rowNumber, colNumber );
    }

    int** squares  = board.sendBoard();
    int* expectedSquares = Data::getExcpectedBoard( dataNumber );

    int k = 0;

    for ( int i = 0; i < dimension; i++ )
    {
        for ( int j = 0; j < dimension; j++ )
            QCOMPARE( squares[i][j], expectedSquares[k++] );
    }
}



QTEST_APPLESS_MAIN(TestFifteen)

#include "testfifteen.moc"
