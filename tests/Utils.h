
#include <numeric>
#include <vector>

#include <gtest/gtest.h>


static void checkTiles(uint size, const std::vector<size_t>& tiles)
{
    uint tilesCount = size * size;
    std::vector<uint> testValues(tilesCount);
    std::iota(testValues.begin(), testValues.end(), 0);
 
    for (uint i = 0; i < tilesCount; i++)
    {
        EXPECT_NE(std::find(testValues.begin(), testValues.end(), tiles[i]), testValues.end());
    }
};

