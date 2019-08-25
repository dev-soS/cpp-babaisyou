#include "Catch2/catch.hpp"

#include "Map.hpp"

TEST_CASE("Map::Default Constructor", "[Map]")
{
    using Vec = std::vector<Block*>;

    Map<10, 10> map;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            REQUIRE(map[i][j] == Vec{});
        }
    }
}

TEST_CASE("Map::[]Operator Overloading","[Map]")
{
    Block block1(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
    Block block2(BlockId::BABA, BlockType::ENTITY, { Property::YOU }, "         ");
    Block block3(BlockId::BABA, BlockType::ENTITY, { Property::WIN }, "         ");
    Block block4(BlockId::BABA, BlockType::ENTITY, { Property::STOP }, "         ");

    Map<2,2> map;

    map[0][0].push_back(&block1);
    map[0][1].push_back(&block2);
    map[1][0].push_back(&block3);
    map[1][1].push_back(&block4);

    using Vec = std::vector<Block*>;

    REQUIRE(map[0][0] == Vec{ &block1 });
    REQUIRE(map[0][1] == Vec{ &block2 });
    REQUIRE(map[1][0] == Vec{ &block3 });
    REQUIRE(map[1][1] == Vec{ &block4 });
}

TEST_CASE("Map::getWidth","[Map]")
{
    Map<10,10> map;
    REQUIRE(map.getWidth() == 10);
}

TEST_CASE("Map::getHeight", "[Map]")
{
	Map<10, 10> map;
	REQUIRE(map.getHeight() == 10);
}

TEST_CASE("Map::Update", "[Map]")
{
	Map<10, 10> map;

	map[1][1].push_back(&Text::baba);
	map[1][2].push_back(&Text::is);
	map[1][3].push_back(&Text::you);

	REQUIRE(!Entity::baba.containProperty(Property::YOU));
	REQUIRE(map.update());
	REQUIRE(Entity::baba.containProperty(Property::YOU));

	map[2][1].push_back(&Text::baba);
	map[2][2].push_back(&Text::is);
	map[2][3].push_back(&Text::win);

	REQUIRE(map.update());
	REQUIRE(Entity::baba.containProperty(Property::YOU));
	REQUIRE(Entity::baba.containProperty(Property::WIN));

	map[3][1].push_back(&Text::flag);
	map[3][2].push_back(&Text::is);
	map[3][3].push_back(&Text::baba);

	REQUIRE(map.update());
	REQUIRE(Entity::flag.containProperty(Property::YOU));
	REQUIRE(Entity::flag.containProperty(Property::WIN));

	Map<10, 10> map2;

	map[1][1].push_back(&Text::baba);
	map[1][2].push_back(&Text::is);
	map[1][3].push_back(&Entity::flag);

	REQUIRE(!map2.update());

	map[2][1].push_back(&Text::baba);
	map[2][2].push_back(&Text::flag);
	map[2][3].push_back(&Text::win);

	REQUIRE(map2.update());
	REQUIRE(!Entity::baba.containProperty(Property::WIN));

	map[3][1].push_back(&Text::baba);
	map[3][2].push_back(&Text::is);
	map[3][3].push_back(&Text::win);
	map[3][4].push_back(&Text::you);

	REQUIRE(map2.update());
	REQUIRE(Entity::baba.containProperty(Property::WIN));
	REQUIRE(!Entity::baba.containProperty(Property::YOU));

}