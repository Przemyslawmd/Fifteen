#include <QString>
#include <QtTest>

#include "../Project/Board.h"
#include "../Project/Board.cpp"

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void suiteCreateBoardSolved();
    void testCreateBoardSolved( int size );

    void suiteCreateBoardRandom();
    void testCreateBoardRandom( int size );
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


QTEST_APPLESS_MAIN(TestFifteen)

#include "testfifteen.moc"
