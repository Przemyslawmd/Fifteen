
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

#include "Utils.h"

#include "Board.h"
#include "Types.h"
#include "MappedValues.h"


void runTestChangeBoard(BoardSize firstSize, BoardSize secondSize)
{
    auto board = std::make_unique<Board>(firstSize, BoardMode::NUMERIC);
    board->generateBoard();
    board->generateBoard();
    const auto& values_1 = board->getBoardValues();

    size_t sizeInt = Maps::boardSizeInt.at(firstSize);
    checkTiles(sizeInt, values_1);

    board.reset(new Board(secondSize, BoardMode::NUMERIC));
    board->generateBoard();
    const auto& values_2 = board->getBoardValues();

    sizeInt = Maps::boardSizeInt.at(secondSize);
    checkTiles(sizeInt, values_2);
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

