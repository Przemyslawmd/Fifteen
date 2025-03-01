
#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>


static void checkTiles(size_t size, const std::vector<size_t>& tiles)
{
    size_t tilesCount = size * size;
    std::vector<size_t> testValues(tilesCount);
    std::iota(testValues.begin(), testValues.end(), 0);

    for (size_t tile : tiles)
    {
        ASSERT_TRUE(std::any_of(testValues.begin(), testValues.end(), [tile](size_t test) { return test == tile; }));
    }
};

