
#include <gtest/gtest.h>

#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

    
void runTest(BoardSize boardSize)
{
    auto board = std::make_unique< Board >( boardSize );
    auto values = board->sendBoard();
    uint sizeInt = Maps::boardSizeInt.at( boardSize );
    uint tilesCount = sizeInt * sizeInt;

    EXPECT_EQ(tilesCount, values.size());
    for (uint i = 0; i < tilesCount - 1; i++)
    {
        EXPECT_EQ(values[i], i);
    }
    EXPECT_EQ(values[tilesCount - 1], board->getEmptyTile());   
}


TEST(InitialBoard, Four)
{
    runTest(BoardSize::FOUR);
}


TEST( InitialBoard, Five )
{
    runTest(BoardSize::FIVE);
}


TEST(InitialBoard, Six)
{
    runTest(BoardSize::SIX);
}


TEST(InitialBoard, Seven)
{
    runTest(BoardSize::SEVEN);
}

