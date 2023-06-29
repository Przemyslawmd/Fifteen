
#include "config.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/FileBoard/IOBoard.h"
#include "../src/GraphicBoard/ImageProvider.h"

#include <gtest/gtest.h>


void runTestErrorRestore(std::string fileName, QString errorLog)
{
    const std::string& filePath = IMPROPER_BOARD_DIR + std::string(fileName);

    IOBoard io;
    auto readValues = io.readBoardFromFile(filePath);
    EXPECT_EQ(readValues, std::nullopt);

    QString message = Message::getMessages();
    EXPECT_EQ(message, errorLog);
}


TEST(testErrorRestore, BoardSizeError)
{
    runTestErrorRestore("boardSize", "File error: read board size is not between five and seven");
}

TEST(testErrorRestore, BoardValuesError)
{
    runTestErrorRestore("boardValue", "File error: board value is not a number");
}

TEST(testErrorRestore, BoardSizeNotFitValues_1)
{
    runTestErrorRestore("boardSizeNotFitValues_1", "File error: read board size doesn't fit to read board values");
}

TEST(testErrorRestore, BoardSizeNotFitValues_2)
{
    runTestErrorRestore("boardSizeNotFitValues_2", "File error: read board size doesn't fit to read board values");
}

TEST(testErrorRestore, valueTooHigh)
{
    runTestErrorRestore("valueTooHigh", "File error: improper value");
}

TEST(testErrorRestore, valueRepeated)
{
    runTestErrorRestore("valueRepeated", "File error: improper value");
}

