
#include "config.h"
#include "Utils.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"
#include "../src/FileBoard/IOBoard.h"

#include <gtest/gtest.h>

#include <iostream>
#include <numeric>
#include <vector>


std::unique_ptr<Board> createAndSaveBoard(BoardSize size)
{
    auto board = std::make_unique<Board>(size, BoardMode::NUMERIC);
    auto initialValues = board->randomBoard();
    
    IOBoard io;
    const std::string& filePath = ROOT_DIR + std::string("savedBoard");
    io.writeBoardIntoFile(*board, filePath);
    return board;
}


std::unique_ptr<Board> restoreBoard(std::unique_ptr<Board> board)
{
    IOBoard io;
    const std::string& filePath = ROOT_DIR + std::string("savedBoard");
    auto readValues = io.readBoardFromFile(filePath);
    std::remove(filePath.c_str());

    BoardSize boardSize = Maps::getBoardSizeByInt(readValues->back());
    readValues->pop_back();
    board.reset(new Board(*readValues, boardSize, board->getMode()));
    return board;
}


TEST(testSaveNumericBoard, NoSizeChange)
{
    auto board = createAndSaveBoard(BoardSize::SEVEN);
    auto initialValues = board->sendBoard();

    auto changedValues = board->randomBoard();
    EXPECT_NE(changedValues, initialValues);
 
    auto restoredBoard = restoreBoard(std::move(board));
    auto restoredValues = restoredBoard->sendBoard();
    EXPECT_EQ(initialValues, restoredValues);
}

TEST(testSaveNumericBoard, SizeChanged)
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
