
#include "Utils.h"

#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>

    
void runRandomBoard(BoardSize boardSize)
{
    auto board = std::make_unique< Board >( boardSize );
    auto values = board->randomBoard();
    uint sizeInt = Maps::boardSizeInt.at( boardSize );
    
    Utils utils;
    utils.checkTiles(sizeInt, values);
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

