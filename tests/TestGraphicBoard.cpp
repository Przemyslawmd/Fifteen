
#include "Utils.h"
#include "config.h"

#include "../src/Board.h"
#include "../src/Options.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"
#include "../src/GraphicBoard/ImageProvider.h"

#include <gtest/gtest.h>
#include <QImage>
#include <QString>

#include <numeric>
#include <vector>


void compareImage(QImage& image1, QImage& image2)
{
    EXPECT_EQ(image1.width(), image2.width());
    EXPECT_EQ(image1.height(), image2.height());

    for (int i = 0; i < image1.width(); i++)
    {
        for (int j = 0; j < image1.height(); j++)
        {
            EXPECT_EQ(image1.pixel(i, j), image2.pixel(i, j));
        }
    }
}


void runTestGraphicBoard(BoardSize boardSize, TileSize tileSize, GraphicMode graphicMode, std::string testImages) 
{
    std::string initial = IMAGES_DIR + testImages + "initial.jpg";
    QImage image(QString::fromStdString(initial));

    auto options = std::make_unique<OptionsData>();
    options->graphicMode = graphicMode;
    options->imageToLoad_4 = true;
    options->imageToLoad_5 = true;
    options->imageToLoad_6 = true;
    options->imageToLoad_7 = true;
    Options::saveOptions(std::move(options));
    
    auto imageProvider = std::make_unique< ImageProvider >();
    imageProvider->prepareGraphicBoard(image, tileSize);
    const auto& images = imageProvider->getImages(boardSize);
    
    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    for (uint i = 0; i < sizeInt * sizeInt; i++)
    {
        std::string imagePath = IMAGES_DIR + testImages + std::to_string(i) + ".bmp";
        QImage image(QString::fromStdString(imagePath));
        compareImage(*images.at(i).get(), image);
    }
}


TEST(testGraphicBoard, SIX_CROPPED)
{
    runTestGraphicBoard(BoardSize::SIX, TileSize::_75, GraphicMode::CROPPED, "cropped_6_75/");
}

TEST(testGraphicBoard, FIVE_SCALLED)
{
    runTestGraphicBoard(BoardSize::FIVE, TileSize::_50, GraphicMode::SCALED, "scalled_5_50/");
}

