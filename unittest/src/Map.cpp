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

TEST_CASE("Map::getHeight","[Map]")
{
    Map<10,10> map;
    REQUIRE(map.getHeight() == 10);
}