#include "Catch2/catch.hpp"

#include "Map.hpp"

TEST_CASE("Default Constructor", "[Map]")
{
    Map<10, 10> map;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            REQUIRE(map[i][j] == nullptr);
        }
    }
}
