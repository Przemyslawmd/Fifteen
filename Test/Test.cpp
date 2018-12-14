
#include "Test.h"
#include "Data.h"
#include "../Project/Board.cpp"
#include "../Project/FileBoard/IOBoard.h"
#include "../Project/FileBoard/IOBoard.cpp"
#include "../Project/FileBoard/IOFile.h"
#include "../Project/FileBoard/IOFile.cpp"
#include "../Project/Options.h"
#include "../Project/GraphicBoard/ImageProvider.h"
#include "../Project/MappedValues.cpp"
#include "../Project/MappedValues.h"
#include <QtTest>


void Test::testCreateBoardSolved( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->sendBoard();

    int sizeInt = board->getIntSize();
    QCOMPARE( sizeInt * sizeInt, static_cast< int >( values.size() ));

    for ( int i = 0; i < sizeInt * sizeInt - 1; i++ )
    {
        QCOMPARE( values[i], i + 1 );
    }

    QCOMPARE( values[sizeInt * sizeInt - 1], 0 );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandom( BoardSize size )
{
    Board* board = Board::createBoard( size );
    vector< int >& values = board->randomBoard();
    int boardSizeInt = board->getIntSize();
    checkTiles( boardSizeInt, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandomWithChange( BoardSize firstSize, BoardSize secondSize )
{
    Board* board = Board::createBoard( firstSize );
    board->randomBoard();
    board->randomBoard();
    vector< int >& values = board->randomBoard();

    int boardSizeInt = board->getIntSize();
    checkTiles( boardSizeInt, values );

    board = Board::createBoard( secondSize );
    board->randomBoard();
    values = board->randomBoard();

    boardSizeInt = board->getIntSize();
    checkTiles( boardSizeInt, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testMoveSquareDefined( int testNumber )
{
    Data::DataInit();
    DataCommon& dataTest = Data::getTestVector( testNumber );
    BoardSize boardSize = dataTest.boardSize;
    Board* board = Board::createBoard( boardSize );

    vector< int >& moves = dataTest.moves;
    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        board->checkMove( moves[i] / 10, moves[i] % 10 );
    }

    vector< int >& currentValues  = board->sendBoard();
    vector< int >& expectedSquares = dataTest.expectedSquares;

    QCOMPARE( currentValues, expectedSquares );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testSaveAndLoadBoard( int testNumber )
{
    Data::DataInit();
    DataCommon dataTest = Data::getTestVector( testNumber );
    BoardSize boardSize = dataTest.boardSize;
    Board* board = Board::createBoard( boardSize );

    vector< int > moves = dataTest.moves;
    int numberOfMoves = moves[0];

    for( int i = 1; i <= numberOfMoves ; i++ )
    {
        board->checkMove( moves[i] / 10, moves[i] % 10 );
    }

    IOBoard io;
    QString fileName = "/fileData";
    QString currentDir = QDir::currentPath();
    QString filePath = currentDir + fileName;
    io.saveNumericBoardInFile( *board, filePath );

    board->randomBoard();
    board->randomBoard();

    vector< int > fileValues( 0 );
    io.readBoardFromFile( filePath, fileValues );
    int boardSizeInt = fileValues.back();
    fileValues.pop_back();

    boardSize = Mapped::getBoardSizeByInt( boardSizeInt );
    board->createBoard( fileValues, boardSize );

    vector< int >& currentValues  = board->sendBoard();
    vector< int >& expectedSquares = dataTest.expectedSquares;

    QCOMPARE( currentValues, expectedSquares );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateGraphicBoard( int testNumber )
{
    Data::DataInit();
    DataGraphic testData = Data::getTestGraphic( testNumber );

    QDir currentDir = QDir::currentPath();
    currentDir.cdUp();
    QImage image( currentDir.absolutePath() + "/Test/Images/" + testData.imagesPath + "initial.jpg" );

    unique_ptr< OptionsData > options ( new OptionsData );
    options->graphicMode = testData.mode;
    options->imageToLoad_4 = testData.isFourToBeLoaded;
    options->imageToLoad_5 = testData.isFiveToBeLoaded;
    options->imageToLoad_6 = testData.isSixToBeLoaded;
    options->imageToLoad_7 = testData.isSevenToBeLoaded;
    Options::receiveData( move( options ));

    ImageProvider& imageProvider = ImageProvider::getInstance();
    imageProvider.prepareGraphicBoard( image, testData.squareSize );
    vector< QImage* >& images = imageProvider.getImages( testData.boardSize );

    for ( int i = 1; i < testData.boardSizeInt * testData.boardSizeInt; i++ )
    {
        QImage image( currentDir.absolutePath() + "/Test/Images/" + testData.imagesPath + QString::number( i ) + ".bmp" );
        compareQImage( *images.at( i ), image );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Test::checkTiles( int boardSize, vector< int >& squares )
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

