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
	REQUIRE(block.getProperties() == std::set<Property>({ Property::PUSH, Property::YOU }));
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

TEST_CASE("Block::getBlockId", "[Block]")
{
	Block block(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
	REQUIRE(block.getBlockId() == BlockId::BABA);
}

TEST_CASE("Block::getBlockType", "[Block]")
{
	Block block(BlockId::BABA, BlockType::ENTITY, { Property::PUSH }, "         ");
	REQUIRE(block.getBlockType() == BlockType::ENTITY);
}

TEST_CASE("Entity::Entity", "[Block]")
{
	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");
	REQUIRE(entity.getBlockId() == BlockId::BABA);
	REQUIRE(entity.getBlockType() == BlockType::ENTITY);
	REQUIRE(true);
}

TEST_CASE("Entity::getPosition", "[Block]")
{
	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");
	REQUIRE(entity.getPosition() == std::vector<Entity::Position>());
}

TEST_CASE("Entity::addPosition", "[Block]")
{
	using PosVec = std::vector<Entity::Position>;

	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");

	entity.addPosition(std::make_tuple(0, 0, 0));
	REQUIRE(entity.getPosition() == PosVec{ std::make_tuple(0, 0, 0) });

	entity.addPosition(std::make_tuple(1, 2, 3));
	entity.addPosition(std::make_tuple(4, 10, 2));
	REQUIRE(entity.getPosition() 
		== PosVec{ std::make_tuple(0, 0, 0), std::make_tuple(1, 2, 3), std::make_tuple(4, 10, 2) });
}

TEST_CASE("Entity::modifyPosition", "[Block]")
{
	using PosVec = std::vector<Entity::Position>;

	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");

	entity.addPosition(std::make_tuple(0, 0, 0));
	entity.addPosition(std::make_tuple(1, 2, 3));
	entity.addPosition(std::make_tuple(4, 10, 2));

	entity.modifyPosition(std::make_tuple(1, 2, 3), std::make_tuple(5, 3, 4));
	REQUIRE(entity.getPosition()
		== PosVec{ std::make_tuple(0, 0, 0), std::make_tuple(5, 3, 4), std::make_tuple(4, 10, 2) });

	entity.modifyPosition(std::make_tuple(5, 3, 4), std::make_tuple(2, 10, 5));
	entity.modifyPosition(std::make_tuple(0, 0, 0), std::make_tuple(1, 1, 1));
	REQUIRE(entity.getPosition()
		== PosVec{ std::make_tuple(1, 1, 1), std::make_tuple(2, 10, 5), std::make_tuple(4, 10, 2) });
}

TEST_CASE("Entity::resetPosition", "[Block]")
{
	using PosVec = std::vector<Entity::Position>;

	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU}, "         ");

	entity.addPosition(std::make_tuple(0, 0, 0));
	entity.addPosition(std::make_tuple(1, 2, 3));
	entity.addPosition(std::make_tuple(4, 10, 2));

	entity.resetPosition();
	REQUIRE(entity.getPosition() == PosVec());
}

TEST_CASE("Text::Text", "[Block]")
{
	Entity entity(BlockId::BABA, { Property::PUSH , Property::YOU }, "         ");
	Text text(BlockId::BABA, Property::WIN, { Property::PUSH }, "123456789", &entity);
	REQUIRE(text.getThisEntity() == &entity);
	REQUIRE(text.getRepr() == Property::WIN);
}
