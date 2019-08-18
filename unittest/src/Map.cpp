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

TEST_CASE("Update", "[Map]")
{
	Map<10, 10> map;

	map[1][1] = &Text::baba;
	map[1][2] = &Text::is;
	map[1][3] = &Text::you;

	REQUIRE(!Entity::baba.containProperty(Property::YOU));
	map.update();
	REQUIRE(Entity::baba.containProperty(Property::YOU));
	
}