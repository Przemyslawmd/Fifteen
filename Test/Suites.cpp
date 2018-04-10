
#include <QString>
#include <QtTest>

#include <QImage>
#include "../Project/Board.h"
#include "../Project/Board.cpp"
#include "../Project/IOFile.h"
#include "../Project/IOFile.cpp"
#include "Data.h"
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

    void testMoveSquareDefined( int testNumber );
    void testSaveAndLoadBoard( int testNumber );
    void testCreateGraphicBoard( int testNumber );

    void checkSquares( BoardSize, vector<int>& values );
    void compareQImage( const QImage& a, const QImage& b );
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
    testMoveSquareDefined( 0 );
    testMoveSquareDefined( 1 );
}


void TestFifteen::suiteSaveAndLoadBoard()
{
    testSaveAndLoadBoard( 0 );
    testSaveAndLoadBoard( 1 );
}


void TestFifteen::suiteCreateGraphicBoard()
{
    // BoardSize: 5; SquareSize: 50, GraphicMode: Scalled
    testCreateGraphicBoard( 0 );

    // BoardSize: 6; SquareSize: 75, GraphicMode: Cropped
    testCreateGraphicBoard( 1 );
}


void TestFifteen::suiteUndoMoves()
{


}

/*********************************************************************************/
/* TEST MOVE SQUARE DEFINED ******************************************************/

void TestFifteen::testMoveSquareDefined( int testNumber )
{
    Data::DataInit();
    TestVector dataTest = Data::getTestVector( testNumber );
    BoardSize boardSize = dataTest.boardSize;
    Board* board = Board::createBoard( boardSize );

    vector< int > moves = dataTest.moves;
    int rowNumber;
    int colNumber;
    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        rowNumber = moves[i] / 10;
        colNumber = moves[i] % 10;
        board->checkMove( rowNumber, colNumber );
    }

    vector<int>& values  = board->sendBoard();
    vector<int> expectedSquares = dataTest.expectedSquares;

    for ( int i = 0, k = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            QCOMPARE( values[k], expectedSquares[k] );
            k++;
        }
    }
}

/*********************************************************************************/
/* TEST SAVE AND LOAD BOARD ******************************************************/

void TestFifteen::testSaveAndLoadBoard( int testNumber )
{
    Data::DataInit();
    TestVector dataTest = Data::getTestVector( testNumber );
    BoardSize boardSize = dataTest.boardSize;
    Board* board = Board::createBoard( boardSize );

    vector< int > moves = dataTest.moves;
    int rowNumber;
    int colNumber;
    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        rowNumber = moves[i] / 10;
        colNumber = moves[i] % 10;
        board->checkMove( rowNumber, colNumber );
    }

    IOFile ioFile;
    QString fileName = "/fileData";
    QString currentDir = QDir::currentPath();
    QString filePath = currentDir + fileName;
    ioFile.saveNumericBoardInFile( *board, filePath );

    board->randomBoard();
    board->randomBoard();

    unique_ptr< vector<int> > valuesFromFile = ioFile.readBoardFromFile( filePath );
    boardSize = (BoardSize) valuesFromFile->back();
    valuesFromFile->pop_back();
    board->createBoard( std::move( valuesFromFile ), boardSize );
    vector<int>& values  = board->sendBoard();

    vector< int > expectedSquares = dataTest.expectedSquares;
    int k = 0;

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
        {
            QCOMPARE( values[k], expectedSquares[k] );
            k++;
        }
    }
}

/*********************************************************************************/
/* TEST CREATE GRAPHIC BOARD *****************************************************/

void TestFifteen::testCreateGraphicBoard( int testNumber )
{
    Data::DataInit();
    TestGraphic testData = Data::getTestGraphic( testNumber );

    QDir currentDir = QDir::currentPath();
    currentDir.cdUp();
    QImage image( currentDir.absolutePath() + "/Test/Images/" + testData.imagesPath + "initial.jpg" );

    unique_ptr< OptionsData > options ( new OptionsData );
    options->graphicMode = testData.mode;
    options->fourImageToBeLoaded = testData.isFourToBeLoaded;
    options->fiveImageToBeLoaded = testData.isFiveToBeLoaded;
    options->sixImageToBeLoaded = testData.isSixToBeLoaded;
    options->sevenImageToBeLoaded = testData.isSevenToBeLoaded;
    Options::receiveData( move( options ));

    ImageProvider& imageProvider = ImageProvider::getInstance();
    imageProvider.prepareBoardImage( image, testData.squareSize );
    vector< QImage* >* images = imageProvider.getImages( testData.boardSize );

    for ( int i = 1; i < testData.boardSize * testData.boardSize; i++ )
    {
        QImage image( currentDir.absolutePath() + "/Test/Images/" + testData.imagesPath + QString::number( i ) + ".bmp" );
        compareQImage( *images->at( i ), image );
    }
}

/***********************************************************************/
/* COMPARE QIMAGE ******************************************************/

void TestFifteen::compareQImage( const QImage& imageA, const QImage& imageB )
{
    QCOMPARE( imageA.width(), imageB.width() );
    QCOMPARE( imageA.height(), imageB.height() );

    for ( int i = 0; i < imageA.width(); i++ )
    {
        for ( int j = 0; j < imageA.height(); j++ )
            QCOMPARE( imageA.pixel( i, j ), imageB.pixel( i, j ));
    }
}

/***********************************************************************/
/***********************************************************************/
// Helper method to check whether a board has all square values

void TestFifteen::checkSquares( BoardSize boardSize, vector<int>& squares )
{
    QList<int> values;

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        values.append( i );
    }

    for ( int i = 0; i < boardSize * boardSize; i++ )
    {
        QCOMPARE( values.contains( squares[i] ), true );
        values.removeOne( squares[i] );
    }

    // List should be empty at the end
    QCOMPARE( values.size(), 0 );
}

QTEST_APPLESS_MAIN(TestFifteen)

#include "Suites.moc"

