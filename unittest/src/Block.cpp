#include "Catch2/catch.hpp"

#include "Block.hpp"
#include "Enums.hpp"

TEST_CASE("Block::Block", "[Block]")
{
	Block block(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
	REQUIRE(true);
}

TEST_CASE("Block::containProperty", "[Block]")
{
	Block block(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
	REQUIRE(block.containProperty(Property::PUSH));
	REQUIRE(!block.containProperty(Property::YOU));
}

TEST_CASE("Block::getProperties", "[Block]")
{
	Block block(BlockId::BABA, BlockType::ENTITY, { Property::PUSH, Property::YOU }, "         ");
	REQUIRE(block.getProperties() == std::set({ Property::PUSH, Property::YOU }));
}

TEST_CASE("Block::addProperty", "[Block]")
{
	Block block1(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
	block1.addProperty(Property::YOU);
	REQUIRE(block1.containProperty(Property::YOU));
	REQUIRE(block1.containProperty(Property::PUSH));
	REQUIRE(!block1.containProperty(Property::STOP));
	REQUIRE(!block1.containProperty(Property::WIN));

	Block block2(BlockId::BABA, BlockType::TEXT, { Property::PUSH }, "         ");
	block2.addProperty({ Property::STOP, Property::WIN });
	REQUIRE(block2.containProperty(Property::PUSH));
	REQUIRE(block2.containProperty(Property::STOP));
	REQUIRE(block2.containProperty(Property::WIN));
	REQUIRE(!block2.containProperty(Property::YOU));
}

TEST_CASE("Block::removeProperty", "[Block]")
{
	Block block(BlockId::BABA, BlockType::TEXT, { Property::PUSH }, "         ");
	block.removeProperty(Property::PUSH);
	block.removeProperty(Property::STOP);
	REQUIRE(!block.containProperty(Property::PUSH));
	REQUIRE(!block.containProperty(Property::STOP));

	block.addProperty({ Property::STOP, Property::WIN });
	block.removeProperty({ Property::PUSH, Property::WIN });
	REQUIRE(!block.containProperty(Property::PUSH));
	REQUIRE(!block.containProperty(Property::WIN));
	REQUIRE(block.containProperty(Property::STOP));
}

TEST_CASE("Block::Entity", "[Block]")
{
	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");
	REQUIRE(true);
}

TEST_CASE("Block::Text", "[Block]")
{
	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU }, "         ");
	Text text(BlockId::BABA, { Property::PUSH }, "123456789", &entity);
	REQUIRE(text.getThisEntity() == &entity);
}
