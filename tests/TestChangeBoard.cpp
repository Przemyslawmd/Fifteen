
#include "Utils.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>


void runTestChangeBoard(BoardSize firstSize, BoardSize secondSize)
{
    auto board = std::make_unique<Board>(firstSize);
    board->randomBoard();
    board->randomBoard();
    auto const& values_1 = board->randomBoard();
    
    Utils utils;
    uint sizeInt = Maps::boardSizeInt.at(firstSize);
    utils.checkTiles(sizeInt, values_1);

    board.reset(new Board(secondSize));
    board->randomBoard();
    auto const& values_2 = board->randomBoard();

    sizeInt = Maps::boardSizeInt.at(secondSize);
    utils.checkTiles(sizeInt, values_2);
}


TEST(testChangeBoard, BoardSizeFourToSeven)
{
    runTestChangeBoard(BoardSize::FOUR, BoardSize::SEVEN);
}

TEST(testChangeRandom, BoardSizeSevenToFive)
{
    runTestChangeBoard(BoardSize::SEVEN, BoardSize::FIVE);
}

TEST(testChangeBoard, BoardSizeSixToSeven)
{
    runTestChangeBoard(BoardSize::SIX, BoardSize::SEVEN);
}

TEST(testChangeBoard, BoardSizeSevenToSeven)
{
    runTestChangeBoard(BoardSize::SEVEN, BoardSize::SEVEN);
}

