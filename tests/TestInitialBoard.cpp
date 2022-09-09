
#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

#include <gtest/gtest.h>

    
void runTestInitialBoard(BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize );
    auto values = board->sendBoard();
    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    uint tilesCount = sizeInt * sizeInt;

    EXPECT_EQ(tilesCount, values.size());
    for (uint i = 0; i < tilesCount - 1; i++)
    {
        EXPECT_EQ(values[i], i);
    }
    EXPECT_EQ(values[tilesCount - 1], board->getEmptyTile());   
}

TEST(testInitialBoard, Four)
{
    runTestInitialBoard(BoardSize::FOUR);
}

TEST(testInitialBoard, Five)
{
    runTestInitialBoard(BoardSize::FIVE);
}

TEST(testInitialBoard, Six)
{
    runTestInitialBoard(BoardSize::SIX);
}

TEST(testInitialBoard, Seven)
{
    runTestInitialBoard(BoardSize::SEVEN);
}

