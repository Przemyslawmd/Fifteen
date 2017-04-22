#include <QString>
#include <QtTest>

#include "../Board.h"
#include "../Board.cpp"

class TestFifteen : public QObject
{
    Q_OBJECT

public:
    TestFifteen();

private Q_SLOTS:
    void testCase();
};

TestFifteen::TestFifteen()
{
}

void TestFifteen::testCase()
{
    Board board(4);

    int** squares = board.sendBoard();

    int k = 1;

    for ( int i = 0; i < 4; i++)
    {
        for ( int j = 0; j < 4; j++)
        {
            if ( i != 3 || j != 3 )
                QCOMPARE( squares[i][j], k++);
            else
                QCOMPARE( squares[i][j], 1);
        }
    }

    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestFifteen)

#include "testfifteen.moc"
