
#include <numeric>
#include <vector>

#include <gtest/gtest.h>
#include <QImage>
#include <QString>

#include "Utils.h"
#include "config.h"

#include "../src/Board.h"
#include "../src/Options.h"
#include "../src/Types.h"
#include "../src/MappedValues.h"
#include "../src/GraphicBoard/ImageProvider.h"


void compareImage(const QImage& image1, const QImage& image2)
{
    ASSERT_EQ(image1.width(), image2.width());
    ASSERT_EQ(image1.height(), image2.height());

    for (size_t i = 0; i < image1.width(); i++)
    {
        for (size_t j = 0; j < image1.height(); j++)
        {
            ASSERT_EQ(image1.pixel(i, j), image2.pixel(i, j));
        }
    }
}


void runTestGraphicBoard(BoardSize boardSize, TileSize tileSize, GraphicMode graphicMode, const std::string& testImages) 
{
    const auto& initial = IMAGES_DIR + testImages + "initial.jpg";
    QImage image(QString::fromStdString(initial));

    OptionsData options;
    options.graphicMode = graphicMode;
    options.imageToLoad_4 = true;
    options.imageToLoad_5 = true;
    options.imageToLoad_6 = true;
    options.imageToLoad_7 = true;
    options.tileSize = tileSize;
    options.numberColor = NumberColor::NO;
    options.squareColor = TileColor::BLUE;
    Options::saveOptions(options);

    auto imageProvider = std::make_unique<ImageProvider>();
    imageProvider->prepareGraphicBoard(image, Maps::tileSizeInt.at(tileSize));
    const auto& images = imageProvider->getImages(boardSize);

    uint sizeInt = Maps::boardSizeInt.at(boardSize);
    for (uint i = 0; i < sizeInt * sizeInt; i++)
    {
        const auto& imagePath = IMAGES_DIR + testImages + std::to_string(i) + ".bmp";
        QImage image(QString::fromStdString(imagePath));
        compareImage(images.at(i), image);
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

