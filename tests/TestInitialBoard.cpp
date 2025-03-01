
#include <gtest/gtest.h>

#include "Board.h"
#include "Types.h"
#include "MappedValues.h"


void runTestInitialBoard(BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize, BoardMode::NUMERIC);
    const auto& values = board->getBoardValues();
    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    uint tilesCount = sizeInt * sizeInt;
    
    ASSERT_EQ(tilesCount, values.size());
    for (uint i = 0; i < tilesCount - 1; i++)
    {
        ASSERT_EQ(values[i], i);
    }
    ASSERT_EQ(values[tilesCount - 1], board->getNullValue());
}


TEST(testInitialBoard, BoardSizeFour)
{
    runTestInitialBoard(BoardSize::FOUR);
}

TEST(testInitialBoard, BoardSizeFive)
{
    runTestInitialBoard(BoardSize::FIVE);
}

TEST(testInitialBoard, BoardSizeSix)
{
    runTestInitialBoard(BoardSize::SIX);
}

TEST(testInitialBoard, BoardSizeSeven)
{
    runTestInitialBoard(BoardSize::SEVEN);
}

