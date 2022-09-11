
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
    auto values = board->randomBoard();
    
    Utils utils;
    uint sizeInt = Maps::boardSizeInt.at(firstSize);
    utils.checkTiles(sizeInt, values);

    board.reset(new Board(secondSize));
    board->randomBoard();
    values = board->randomBoard();

    sizeInt = Maps::boardSizeInt.at(secondSize);
    utils.checkTiles(sizeInt, values);
}


TEST(testChangeBoard, FourToSeven)
{
    runTestChangeBoard(BoardSize::FOUR, BoardSize::SEVEN);
}

TEST(testChangeRandom, SevenToFive)
{
    runTestChangeBoard(BoardSize::SEVEN, BoardSize::FIVE);
}

TEST(testChangeBoard, SixToSeven)
{
    runTestChangeBoard(BoardSize::SIX, BoardSize::SEVEN);
}

TEST(testChangeBoard, SevenToSeven)
{
    runTestChangeBoard(BoardSize::SEVEN, BoardSize::SEVEN);
}

