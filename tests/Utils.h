
#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>


static void checkTiles(uint size, const std::vector<size_t>& tiles)
{
    size_t tilesCount = size * size;
    std::vector<size_t> testValues(tilesCount);
    std::iota(testValues.begin(), testValues.end(), 0);

    for (size_t i = 0; i < tilesCount; i++)
    {
        EXPECT_NE(std::find(testValues.begin(), testValues.end(), tiles[i]), testValues.end());
    }
};

