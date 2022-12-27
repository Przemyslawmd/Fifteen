
#include "config.h"

#include "../src/Board.h"
#include "../src/Types.h"
#include "../src/FileBoard/IOBoard.h"
#include "../src/GraphicBoard/ImageProvider.h"

#include <gtest/gtest.h>

#include <QString>


void runTestErrorRestore(std::string fileName, QString errorLog)
{
    std::string filePath = IMPROPER_BOARD_DIR + std::string(fileName);
    
    IOBoard io;
    auto readValues = io.readBoardFromFile(QString::fromStdString(filePath));
    
    EXPECT_EQ(readValues, nullptr);

    QString message = Message::getMessages();
    EXPECT_EQ(message, errorLog);
}


TEST(testErrorRestore, BoardSizeError)
{
    runTestErrorRestore("improperBoardSize", "Error reading file : size of a board");
}

TEST(testErrorRestore, BoardModeError)
{
    runTestErrorRestore("improperBoardMode", "Error reading file : kind of a board");
}

TEST(testErrorRestore, BoardValuesError)
{
    runTestErrorRestore("improperBoardValues", "Error reading file : board values");
}

TEST(testErrorRestore, BoardNotAllValues)
{
    runTestErrorRestore("improperBoardNotAllValues", "Error reading file : board values");
}

