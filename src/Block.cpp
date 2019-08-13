#include "Block.hpp"

Text Text::baba(BlockId::BABATEXT, { Property::PUSH }, "B A   B A", &Entity::baba);
Text Text::is(BlockId::ISTEXT, { Property::PUSH }, "   I S   ");
Text Text::you(BlockId::YOUTEXT, { Property::PUSH }, "   YOU   ");
Text Text::flag(BlockId::FLAGTEXT, { Property::PUSH }, "F L   A G", &Entity::flag);
Text Text::win(BlockId::WINTEXT, { Property::PUSH }, "   WIN   ");
Text Text::push(BlockId::PUSHTEXT, { Property::PUSH }, "P U   S H");
Text Text::stop(BlockId::STOPTEXT, { Property::PUSH }, "S T   O P");

Entity Entity::baba(BlockId::BABAENTITY, {}, "/  OOOO O");
Entity Entity::flag(BlockId::FLAGENTITY, {}, " |> | ===");

// CLASS BLOCK PART =======================================

Block::Block(BlockId block_id, std::set<Property> property, const char* block_visual) : block_id(block_id), properties(property)
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
	if ( properties.find(property) == properties.end() )
	{
		return false;
	}
	else
	{
		return true;
	}
}

BlockId Block::getBlockId()
{
	return block_id;
}
	
// CLASS TEXT PART ========================================

Text::Text(BlockId block_id, std::set<Property> property, const char* block_visual, Entity* this_entity) : Block(block_id, property, block_visual), this_entity(this_entity)
{

}

Entity* Text::getThisEntity()
{
	return this_entity;
}

// CLASS ENTITY PART ======================================

Entity::Entity(BlockId block_id, std::set<Property> property, const char* block_visual) : Block(block_id, property, block_visual)
{

}
