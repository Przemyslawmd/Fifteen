
#include "Utils.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>

    
void runTestRandomBoard(BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize);
    auto values = board->randomBoard();
    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    
    Utils utils;
    utils.checkTiles(sizeInt, values);
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

