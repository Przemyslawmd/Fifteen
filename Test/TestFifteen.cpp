
#include <QString>
#include <QtTest>

#include <QImage>
#include "../Project/Board.h"
#include "../Project/Board.cpp"
#include "../Project/IOFile.h"
#include "../Project/IOFile.cpp"
#include "Data.h"

class TestFifteen : public QObject
{
    Q_OBJECT

private Q_SLOTS:   

    void suiteCreateBoardSolved();
    void suiteCreateBoardRandom();
    void suiteMoveSquareDefined();
    void suiteSaveAndLoadBoard();
    void suiteCreateGraphicBoard();

    void testCreateBoardSolved( BoardSize );
    void testCreateBoardRandom( BoardSize );
    void testCreateBoardRandomWithChange( BoardSize sizeFirst, BoardSize sizeSecond );
    void testMoveSquareDefined( int testNumber );
    void testSaveAndLoadBoard( int testNumber );
    void testCreateGraphicBoard( int testNumber );

    void checkSquares( BoardSize, int** squares );
    void compareQImage( const QImage& a, const QImage& b );
};


void TestFifteen::suiteCreateBoardSolved()
{
    testCreateBoardSolved( BoardSize::FOUR );
    testCreateBoardSolved( BoardSize::SIX );
}


void TestFifteen::suiteCreateBoardRandom()
{
    testCreateBoardRandom( BoardSize::FIVE );
    testCreateBoardRandom( BoardSize::SEVEN );
    testCreateBoardRandomWithChange( BoardSize::FIVE, BoardSize::SIX );
    testCreateBoardRandomWithChange( BoardSize::SEVEN, BoardSize::FOUR );
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

/*********************************************************************************/
/* TEST CREATE BOARD SOLVED ******************************************************/
// Test creating initial state of a board, values in a board should be sorted

void TestFifteen::testCreateBoardSolved( BoardSize size )
{
    Board* board = Board::createBoard( size );
    int** squares = board->sendBoard();

    for ( int i = 0, k = 1; i < size; i++)
    {
        for ( int j = 0; j < size; j++)
        {
            if ( i != ( size - 1 ) || j != ( size - 1 ) )
                QCOMPARE( squares[i][j], k++ );
            else
                QCOMPARE( squares[i][j], 0 );
        }
    }
}

/*********************************************************************************/
/* TEST CREATE RANDOM BOARD ******************************************************/
// After random board check whether a board has all values

void TestFifteen::testCreateBoardRandom( BoardSize size )
{
    Board* board = Board::createBoard( size );
    int** squares = board->randomBoard();
    checkSquares( size, squares );
}

/*********************************************************************************/
/* TEST CREATE BOARD RANDOM WITH CHANGE ******************************************/

void TestFifteen::testCreateBoardRandomWithChange( BoardSize sizeFirst, BoardSize sizeSecond )
{
    Board* board = Board::createBoard( sizeFirst );
    board->randomBoard();
    board->randomBoard();
    int** squares = board->randomBoard();

    checkSquares( sizeFirst, squares );

    board = Board::createBoard( sizeSecond );
    board->randomBoard();
    squares = board->randomBoard();

    checkSquares( sizeSecond, squares );
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

    int** squares  = board->sendBoard();
    vector< int > expectedSquares = dataTest.expectedSquares;

    for ( int i = 0, k = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
            QCOMPARE( squares[i][j], expectedSquares[k++] );
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
    ioFile.saveNumericBoardInFile( board, filePath );

    board->randomBoard();
    board->randomBoard();

    int** readValues = ioFile.readBoardFromFile( filePath );
    board->createBoard( readValues, Options::getBoardSize() );
    int** squares  = board->sendBoard();

    vector< int > expectedSquares = dataTest.expectedSquares;
    int k = 0;

    for ( int i = 0; i < boardSize; i++ )
    {
        for ( int j = 0; j < boardSize; j++ )
            QCOMPARE( squares[i][j], expectedSquares[k++] );
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
    Options::setGraphicMode( testData.mode );
    Options::setImagesToBeLoaded( testData.isFourToBeLoaded, testData.isFiveToBeLoaded, testData.isSixToBeLoaded, testData.isSevenToBeLoaded );

    ImageProvider& imageProvider = ImageProvider::getInstance();
    imageProvider.prepareBoardImage( image, testData.squareSize );
    QImage** images = imageProvider.getImage( testData.boardSize );

    for ( int i = 1; i < testData.boardSize * testData.boardSize; i++ )
    {
        QImage image( currentDir.absolutePath() + "/Test/Images/" + testData.imagesPath + QString::number( i ) + ".bmp" );
        compareQImage( *images[i], image );
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
/* CHECK SQUARES SIZE **************************************************/
// Helper method to check whether a board has all square values

void TestFifteen::checkSquares( BoardSize boardSize, int** squares )
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

QTEST_APPLESS_MAIN(TestFifteen)

#include "TestFifteen.moc"

