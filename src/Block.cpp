#include "Block.hpp"

Text Text::baba(BlockId::BABA, { Property::PUSH }, "B A   B A", &Entity::baba);
Text Text::is(BlockId::IS, { Property::PUSH }, "   I S   ");
Text Text::you(BlockId::YOU, { Property::PUSH }, "   YOU   ");
Text Text::flag(BlockId::FLAG, { Property::PUSH }, "F L   A G", &Entity::flag);
Text Text::win(BlockId::WIN, { Property::PUSH }, "   WIN   ");
Text Text::push(BlockId::PUSH, { Property::PUSH }, "P U   S H");
Text Text::stop(BlockId::STOP, { Property::PUSH }, "S T   O P");

Entity Entity::baba(BlockId::BABA, {}, "/  OOOO O");
Entity Entity::flag(BlockId::FLAG, {}, " |> | ===");

// CLASS BLOCK PART =======================================

Block::Block(BlockId block_id, BlockType block_type, std::set<Property> property, const char* block_visual)
	: block_id(block_id), block_type(block_type), properties(property)
{
	for (int i = 0, k = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j, ++k )
		{
			this->block_visual[i][j] = block_visual[k];
		}
	}
}

void Block::addProperty(Property property)
{
	properties.insert(property);
}

void Block::addProperty(std::set<Property> property)
{
	properties.merge(property);
}

void Block::removeProperty(Property property)
{
	properties.erase(property);
}

void Block::removeProperty(const std::set<Property>& property)
{
	for ( Property p : property )
	{
		properties.erase(p);
	}
}

bool Block::containProperty(Property property) const
{
	return properties.find(property) != properties.end();
}

BlockId Block::getBlockId() const
{
	return block_id;
}

BlockType Block::getBlockType() const
{
	return block_type;
}

// CLASS TEXT PART ========================================

Text::Text(BlockId block_id, std::set<Property> property, const char* block_visual, Entity* this_entity)
	: Block(block_id, BlockType::TEXT, property, block_visual), this_entity(this_entity)
{

}

Entity* Text::getThisEntity() const
{
	return this_entity;
}

// CLASS ENTITY PART ======================================

Entity::Entity(BlockId block_id, std::set<Property> property, const char* block_visual)
	: Block(block_id, BlockType::ENTITY, property, block_visual)
{

}
