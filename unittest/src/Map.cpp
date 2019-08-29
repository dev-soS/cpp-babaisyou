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
/*
TEST_CASE("Map::updateInternal", "[Map]")
{
	Map<10, 10> map;

	map[1][1].push_back(&Text::baba);
	map[1][2].push_back(&Text::is);
	map[1][3].push_back(&Text::you);
	map[1][4].push_back(&Text::flag);

	map[1][6].push_back(&Text::is);

	int x = 1, y = 1;
	REQUIRE(map.updateInternalHorizonal(0, x, y) == 4);
}
*/
TEST_CASE("Map::Update", "[Map]")
{
	Map<10, 10> map;

	std::string visual = "123456789";
	Entity baba_entity(BlockId::BABA, {}, visual);
	Text baba_text(BlockId::BABA, Property::ENTITY, {}, visual, &baba_entity);

	Entity flag_entity(BlockId::FLAG, {}, visual);
	Text flag_text(BlockId::FLAG, Property::ENTITY, {}, visual, &flag_entity);

	Text is_text(BlockId::IS, Property::INVALID, {}, visual);
	Text you_text(BlockId::YOU, Property::YOU, {}, visual);

	Text win_text(BlockId::WIN, Property::WIN, {}, visual);

	map[0][1].push_back(&baba_text);
	map[0][2].push_back(&is_text);
	map[0][3].push_back(&you_text);

	REQUIRE(!baba_entity.containProperty(Property::YOU));
	REQUIRE(map.update());
	REQUIRE(baba_entity.containProperty(Property::YOU));

	map[2][1].push_back(&baba_text);
	map[2][2].push_back(&is_text);
	map[2][3].push_back(&win_text);

	REQUIRE(map.update());
	REQUIRE(baba_entity.containProperty(Property::YOU));
	REQUIRE(baba_entity.containProperty(Property::WIN));

	map[4][1].push_back(&flag_text);
	map[5][1].push_back(&is_text);
	map[6][1].push_back(&win_text);

	REQUIRE(map.update());
	REQUIRE(flag_entity.containProperty(Property::WIN));

	Map<10, 10> map2;

	Entity baba_entity2(BlockId::BABA, {}, visual);
	Text baba_text2(BlockId::BABA, Property::ENTITY, {}, visual, &baba_entity2);

	Entity flag_entity2(BlockId::FLAG, {}, visual);
	Text flag_text2(BlockId::FLAG, Property::ENTITY, {}, visual, &flag_entity2);

	Text is_text2(BlockId::IS, Property::INVALID, {}, visual);
	Text you_text2(BlockId::YOU, Property::YOU, {}, visual);

	Text win_text2(BlockId::WIN, Property::WIN, {}, visual);


	map2[1][1].push_back(&baba_text);
	map2[1][2].push_back(&is_text2);
	map2[1][3].push_back(&flag_entity2);

	REQUIRE(!map2.update());

	map2[2][1].push_back(&baba_text2);
	map2[2][2].push_back(&flag_text2);
	map2[2][3].push_back(&win_text2);

	REQUIRE(!map2.update());
	REQUIRE(!baba_entity2.containProperty(Property::WIN));

	map2[3][1].push_back(&baba_text2);
	map2[3][2].push_back(&is_text2);
	map2[3][3].push_back(&win_text2);
	map2[3][4].push_back(&you_text2);

	REQUIRE(map2.update());
	REQUIRE(baba_entity2.containProperty(Property::WIN));
	REQUIRE(!baba_entity2.containProperty(Property::YOU));
	
}