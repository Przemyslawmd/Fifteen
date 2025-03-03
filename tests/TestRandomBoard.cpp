
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

#include "Board.h"
#include "Types.h"
#include "MappedValues.h"


void runTestRandomBoard(BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize, BoardMode::NUMERIC);
    board->generateBoard();
    auto values = board->getBoardValues();
    size_t sizeInt = Maps::boardSizeInt.at(boardSize);

    checkTiles(sizeInt, values);
}


TEST(testRandomBoard, Four)
{
    runTestRandomBoard(BoardSize::FOUR);
}

TEST(testRandomBoard, Five)
{
    runTestRandomBoard(BoardSize::FIVE);
}

TEST(testRandomBoard, Six)
{
    runTestRandomBoard(BoardSize::SIX);
}

TEST(testRandomBoard, Seven)
{
    runTestRandomBoard(BoardSize::SEVEN);
}

