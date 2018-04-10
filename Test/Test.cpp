
#include "Test.h"
#include "Data.h"
#include "../Project/Board.cpp"
#include "../Project/IOFile.h"
#include "../Project/IOFile.cpp"
#include "../Project/Options.h"
#include "../Project/GraphicBoard/ImageProvider.h"
#include <QtTest>


void Test::testCreateBoardSolved( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->sendBoard();

    for ( int i = 0; i < size * size - 1; i++)
    {
        QCOMPARE( values[i], i + 1 );
    }

    QCOMPARE( values[size * size - 1], 0 );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandom( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->randomBoard();
    checkSquares( size, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandomWithChange( BoardSize firstSize, BoardSize secondSize )
{
    Board* board = Board::createBoard( firstSize );
    board->randomBoard();
    board->randomBoard();
    vector< int >& values = board->randomBoard();

    checkSquares( firstSize, values );

    board = Board::createBoard( secondSize );
    board->randomBoard();
    values = board->randomBoard();

    checkSquares( secondSize, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testMoveSquareDefined( int testNumber )
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
/*********************************************************************************/

void Test::testSaveAndLoadBoard( int testNumber )
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

    unique_ptr< vector< int >> valuesFromFile = ioFile.readBoardFromFile( filePath );
    boardSize = (BoardSize) valuesFromFile->back();
    valuesFromFile->pop_back();
    board->createBoard( std::move( valuesFromFile ), boardSize );
    vector< int >& values  = board->sendBoard();

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
/*********************************************************************************/

void Test::testCreateGraphicBoard( int testNumber )
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

/*********************************************************************************/
/*********************************************************************************/

void Test::checkSquares( BoardSize boardSize, vector< int >& squares )
{
    QList< int > values;

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

/*********************************************************************************/
/*********************************************************************************/

void Test::compareQImage( const QImage& imageA, const QImage& imageB )
{
    QCOMPARE( imageA.width(), imageB.width() );
    QCOMPARE( imageA.height(), imageB.height() );

    for ( int i = 0; i < imageA.width(); i++ )
    {
        for ( int j = 0; j < imageA.height(); j++ )
        {
            QCOMPARE( imageA.pixel( i, j ), imageB.pixel( i, j ));
        }
    }
}

