
#include <gtest/gtest.h>

#include <numeric>
#include <vector>


class Utils
{
public:
    void checkTiles(uint size, const std::vector<uint>& tiles) 
    {
        uint tilesCount = size * size;
        std::vector< uint > testValues(tilesCount);
        std::iota(testValues.begin(), testValues.end(), 0);
 
        for (uint i = 0; i < tilesCount; i++)
        {
            EXPECT_NE(std::find(testValues.begin(), testValues.end(), tiles[i]), testValues.end());
            //EXPECT_NE(it, testValues.end());
            //testValues.erase(it);
        }
        //EXPECT_EQ(testValues.size(), 0);
    };
};

