
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

    
void runRandomBoard(BoardSize boardSize)
{
    auto board = std::make_unique< Board >( boardSize );
    auto values = board->randomBoard();
    uint sizeInt = Maps::boardSizeInt.at( boardSize );
    
    uint tilesCount = sizeInt * sizeInt;
    std::vector< uint > testValues(tilesCount);
    std::iota(testValues.begin(), testValues.end(), 0);
 
    for ( uint i = 0; i < tilesCount; i++ )
    {
        auto it = std::find(testValues.begin(), testValues.end(), values[i]);
        EXPECT_NE(it, testValues.end());
        testValues.erase(it);
    }
    EXPECT_EQ( testValues.size(), 0 );
}


TEST(RandomBoard, Four)
{
    runRandomBoard(BoardSize::FOUR);
}

TEST(Random, Five)
{
    runRandomBoard(BoardSize::FIVE);
}

TEST(RandomBoard, Six)
{
    runRandomBoard(BoardSize::SIX);
}

TEST(RandomBoard, Seven)
{
    runRandomBoard(BoardSize::SEVEN);
}
