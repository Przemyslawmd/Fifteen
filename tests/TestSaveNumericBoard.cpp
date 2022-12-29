
#include "config.h"
#include "Utils.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"
#include "../src/FileBoard/IOBoard.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>


std::unique_ptr<Board> createAndSaveBoard(BoardSize size)
{
    auto board = std::make_unique<Board>(size, BoardMode::NUMERIC);
    auto initialValues = board->randomBoard();
    
    IOBoard io;
    std::string filePath = ROOT_DIR + std::string("savedBoard");
    io.writeBoardIntoFile(*board, QString::fromStdString(filePath));
    return board;
}


std::unique_ptr<Board> restoreBoard(std::unique_ptr<Board> board)
{
    IOBoard io;
    std::string filePath = ROOT_DIR + std::string("savedBoard");
    auto readValues = io.readBoardFromFile(QString::fromStdString(filePath));
    
    BoardSize boardSize = Maps::getBoardSizeByInt(readValues->back());
    readValues->pop_back();
    board.reset(new Board(*readValues, boardSize, board->getMode()));
    return board;
}


void runTestSaveNumericBoard()
{
    auto board = createAndSaveBoard(BoardSize::SEVEN);
    auto initialValues = board->sendBoard();

    auto changedValues = board->randomBoard();
    EXPECT_NE(changedValues, initialValues);
 
    auto restoredBoard = restoreBoard(std::move(board));
    auto restoredValues = restoredBoard->sendBoard();
    EXPECT_EQ(initialValues, restoredValues);    
}


void runTestSaveNumericBoardWithChangeSize()
{
    auto board = createAndSaveBoard(BoardSize::SEVEN);
    auto initialValues = board->sendBoard();

    board.reset(new Board(BoardSize::FIVE, BoardMode::NUMERIC));
    auto changedValues = board->randomBoard();
    EXPECT_NE(changedValues, initialValues);

    auto restoredBoard = restoreBoard(std::move(board));
    auto restoredValues = restoredBoard->sendBoard();
    EXPECT_EQ(initialValues, restoredValues);  
}


TEST(testSaveNumericBoard, NoSizeChange)
{
    runTestSaveNumericBoard();
}

TEST(testSaveNumericBoard, WithSizeChange)
{
    runTestSaveNumericBoardWithChangeSize();
}

