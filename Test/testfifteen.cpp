#include <QString>
#include <QtTest>

#include "../Project/Board.h"
#include "../Project/Board.cpp"

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void testCaseCreatingBoard();
    void testCreatingBoard( int size );

    void testCaseGeneratingBoard();
    void testGeneratingBoard( int size );
};

void TestFifteen::testCaseCreatingBoard()
{
    testCreatingBoard( 4 );
    testCreatingBoard( 6 );
}


void TestFifteen::testCaseGeneratingBoard()
{
    testGeneratingBoard( 5 );
    testGeneratingBoard( 7 );
}

/**********************************************/
/* TEST CREATING BOARD ************************/
// Test creating board at the beginning
// Board should be created and solved

void TestFifteen::testCreatingBoard( int size )
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
/* TEST GENERATING BOARD **********************/
// Test generating board
// Values are not sorted

void TestFifteen::testGeneratingBoard( int size )
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
