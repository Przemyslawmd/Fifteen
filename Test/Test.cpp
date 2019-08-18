
#include "Test.h"
#include "../Project/Board.cpp"
#include "../Project/FileBoard/IOBoard.h"
#include "../Project/FileBoard/IOBoard.cpp"
#include "../Project/FileBoard/IODataModel.h"
#include "../Project/FileBoard/IODataModel.cpp"
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
    auto values = board->sendBoard();
    uint sizeInt = Mapped::boardSizeInt.at( size );
    uint tilesCount = sizeInt * sizeInt;

    QCOMPARE( tilesCount, values.size() );

    for ( uint i = 0; i < tilesCount - 1; i++ )
    {
        QCOMPARE( values[i], i );
    }

    QCOMPARE( values[tilesCount - 1], board->getEmptyTile() );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandom( BoardSize size )
{
    Board* board = Board::createBoard( size );
    auto& values = board->randomBoard();
    uint sizeInt = Mapped::boardSizeInt.at( size );
    checkTiles( sizeInt, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateBoardRandomWithChange( BoardSize firstSize, BoardSize secondSize )
{
    Board* board = Board::createBoard( firstSize );
    board->randomBoard();
    board->randomBoard();
    auto values = board->randomBoard();

    uint sizeInt = Mapped::boardSizeInt.at( firstSize );
    checkTiles( sizeInt, values );

    board = Board::createBoard( secondSize );
    board->randomBoard();
    values = board->randomBoard();

    sizeInt = Mapped::boardSizeInt.at( secondSize );
    checkTiles( sizeInt, values );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testMoveSquareDefined( vector< int >& moves, vector< uint >& expectedValues, BoardSize boardSize )
{
    Board* board = Board::createBoard( boardSize );

    for( int move : moves  )
    {
        board->checkMove( move / 10, move % 10 );
    }

    auto values  = board->sendBoard();
    QCOMPARE( values, expectedValues );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testSaveAndLoadBoard( vector< int >& moves, vector< uint >& expectedValues, BoardSize boardSize )
{
    Board* board = Board::createBoard( boardSize );

    for( int move : moves )
    {
        board->checkMove( move / 10, move % 10 );
    }

    IOBoard io;
    QString filePath = QDir::currentPath() + "/fileData";
    io.writeBoardIntoFile( *board, BoardMode::NUMERIC, filePath );

    board->randomBoard();
    board->randomBoard();

    auto readValues = io.readBoardFromFile( filePath );
    uint boardSizeInt = readValues->back();
    readValues->pop_back();

    boardSize = Mapped::getBoardSizeByInt( boardSizeInt );
    board->createBoard( *readValues, boardSize );

    auto values  = board->sendBoard();
    QCOMPARE( values, expectedValues );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testLoadImproperBoard( QString fileName, QString expectedMessage )
{
    QDir currentDir = QDir::currentPath();
    currentDir.cdUp();
    QString filePath = currentDir.absolutePath() + "/Test/SavedBoards/" + fileName;

    IOBoard io;
    auto readValues = io.readBoardFromFile( filePath );

    QCOMPARE( readValues, nullptr );
    QCOMPARE( expectedMessage, Message::getMessages() );
}

/*********************************************************************************/
/*********************************************************************************/

void Test::testCreateGraphicBoard( DataGraphic& data )
{
    QDir currentDir = QDir::currentPath();
    currentDir.cdUp();
    QImage image( currentDir.absolutePath() + "/Test/Images/" + data.imagesPath + "initial.jpg" );

    unique_ptr< OptionsData > options ( new OptionsData );
    options->graphicMode = data.mode;
    options->imageToLoad_4 = data.isFourToBeLoaded;
    options->imageToLoad_5 = data.isFiveToBeLoaded;
    options->imageToLoad_6 = data.isSixToBeLoaded;
    options->imageToLoad_7 = data.isSevenToBeLoaded;
    Options::receiveData( move( options ));

    ImageProvider& imageProvider = ImageProvider::getInstance();
    imageProvider.prepareGraphicBoard( image, data.tileSize );
    auto& images = imageProvider.getImages( data.size );

    uint sizeInt = Mapped::boardSizeInt.at( data.size );
    for ( uint i = 0; i < sizeInt * sizeInt; i++ )
    {
        QImage image( currentDir.absolutePath() + "/Test/Images/" + data.imagesPath + QString::number( i ) + ".bmp" );
        compareQImage( *images.at( i ).get(), image );
    }
}

/*********************************************************************************/
/*********************************************************************************/

void Test::checkTiles( uint boardSize, vector< uint >& tiles )
{
    QList< uint > values;
    uint tilesCount = boardSize * boardSize;

    for ( uint i = 0; i < tilesCount; i++ )
    {
        values.append( i );
    }

    for ( uint i = 0; i < tilesCount; i++ )
    {
        QCOMPARE( values.contains( tiles[i] ), true );
        values.removeOne( tiles[i] );
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

