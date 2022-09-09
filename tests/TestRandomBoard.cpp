
#include "Utils.h"

#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

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

