
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

#include "Board.h"
#include "Types.h"
#include "MappedValues.h"


void runTestMoves(const std::vector<int>& moves, const std::vector<uint>& expectedValues, BoardSize boardSize)
{
    auto board = std::make_unique<Board>(boardSize, BoardMode::NUMERIC);
    for (int move : moves)
    {
        board->checkMove(move / 10, move % 10);
    }
    
    const auto& values = board->getBoardValues();
    for (int i = 0; i < values.size(); ++i)
    {
        ASSERT_EQ(values[i], expectedValues[i]);
    }
}


TEST(testMoves, BoardSizeFour)
{
    runTestMoves({ 23, 23, 22, 10, 11, 21, 22, 32, 33, 23, 22, 21, 20 },
                 { 0, 1, 2, 3, 4, 5, 6, 7, 15, 8, 9, 14, 12, 13, 11, 10 },
                 BoardSize::FOUR);
}

TEST(testMoves, BoardSizeFive)
{
    runTestMoves({ 34, 24, 24, 11, 14, 13, 12, 02, 03, 02, 01, 00, 00, 10, 11, 21, 31, 30, 40, 41 },
                 { 5, 0, 1, 3, 4, 6, 11, 2, 7, 8, 10, 16, 12, 13, 9, 20, 15, 17, 18, 14, 21, 24, 22, 23, 19 }, 
                 BoardSize::FIVE);
}

