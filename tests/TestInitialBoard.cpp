
#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"

#include <gtest/gtest.h>

    
void runTestInitialBoard(BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize );
    auto const& values = board->sendBoard();
    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    uint tilesCount = sizeInt * sizeInt;
    
    ASSERT_EQ(tilesCount, values.size());
    for (uint i = 0; i < tilesCount - 1; i++)
    {
        EXPECT_EQ(values[i], i);
    }
    EXPECT_EQ(values[tilesCount - 1], board->getEmptyTile());   
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

