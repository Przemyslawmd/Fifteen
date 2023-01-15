
#include "Utils.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>


void runTestChangeBoard(BoardSize firstSize, BoardSize secondSize)
{
    auto board = std::make_unique<Board>(firstSize, BoardMode::NUMERIC);
    board->randomBoard();
    board->randomBoard();
    auto const& values_1 = board->randomBoard();
    
    uint sizeInt = Maps::boardSizeInt.at(firstSize);
    Utils::checkTiles(sizeInt, values_1);

    board.reset(new Board(secondSize, BoardMode::NUMERIC));
    board->randomBoard();
    auto const& values_2 = board->randomBoard();

    sizeInt = Maps::boardSizeInt.at(secondSize);
    Utils::checkTiles(sizeInt, values_2);
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

