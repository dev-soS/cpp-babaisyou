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

TEST_CASE("Map::Update", "[Map]")
{
	Map<10, 10> map;

	map[1][1] = &Text::baba;
	map[1][2] = &Text::is;
	map[1][3] = &Text::you;

	REQUIRE(!Entity::baba.containProperty(Property::YOU));
	REQUIRE(map.update());
	REQUIRE(Entity::baba.containProperty(Property::YOU));

	map[2][1] = &Text::is;


	Map<10, 10> map2;

	map[1][1] = &Text::baba;
	map[1][2] = &Text::is;
	map[1][3] = &Entity::flag;

	REQUIRE(!map2.update());

	map[2][1] = &Text::baba;
	map[2][2] = &Text::flag;
	map[2][3] = &Text::win;

	REQUIRE(map2.update());
	REQUIRE(!Entity::baba.containProperty(Property::WIN));
}