
#include "Utils.h"

#include "../Project/Board.h"
#include "../Project/Types.h"
#include "../Project/MappedValues.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>


void runChangeBoard(BoardSize firstSize, BoardSize secondSize)
{
    auto board = std::make_unique< Board >( firstSize );
    board->randomBoard();
    board->randomBoard();
    auto values = board->randomBoard();
    
    Utils utils;
    uint sizeInt = Maps::boardSizeInt.at( firstSize );
    utils.checkTiles(sizeInt, values);

    board.reset(new Board(secondSize));
    board->randomBoard();
    values = board->randomBoard();

    sizeInt = Maps::boardSizeInt.at( secondSize );
    utils.checkTiles(sizeInt, values);
}


TEST(ChangeBoard, Four)
{
    runChangeBoard(BoardSize::FOUR, BoardSize::SEVEN);
}

TEST(ChangeRandom, Five)
{
    runChangeBoard(BoardSize::SEVEN, BoardSize::FIVE);
}

TEST(ChangeBoard, Six)
{
    runChangeBoard(BoardSize::SIX, BoardSize::SEVEN);
}

TEST(ChangeBoard, Seven)
{
    runChangeBoard(BoardSize::SEVEN, BoardSize::SEVEN);
}

