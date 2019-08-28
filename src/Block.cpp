#include <algorithm>
#include <vector>

#include "Block.hpp"

Text Text::baba(BlockId::BABA, Property::ENTITY, { Property::PUSH }, "B A   B A", &Entity::baba);
Text Text::is(BlockId::IS, Property::INVALID, { Property::PUSH }, "   I S   ");
Text Text::you(BlockId::YOU, Property::YOU, { Property::PUSH }, "   YOU   ");
Text Text::flag(BlockId::FLAG, Property::ENTITY, { Property::PUSH }, "F L   A G", &Entity::flag);
Text Text::win(BlockId::WIN, Property::WIN, { Property::PUSH }, "   WIN   ");
Text Text::push(BlockId::PUSH, Property::PUSH, { Property::PUSH }, "P U   S H");
Text Text::stop(BlockId::STOP, Property::STOP, { Property::PUSH }, "S T   O P");

Entity Entity::baba(BlockId::BABA, {}, "/  OOOO O");
Entity Entity::flag(BlockId::FLAG, {}, " |> | ===");

// CLASS BLOCK PART =======================================

Block::Block(BlockId block_id, BlockType block_type, std::set<Property> property, const std::string& block_visual)
	: block_id(block_id), block_type(block_type), properties(property)
{
	for ( int i = 0, j = 0; i < 3; ++i )
	{
		this->block_visual[i].resize(3);
		for ( int k = 0; k < 3; ++k, ++j )
		{
			this->block_visual[i][k] = block_visual[j];
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

const std::set<Property>& Block::getProperties() const
{
	return properties;
}

bool Block::containProperty(Property property) const
{
	return properties.find(property) != properties.end();
}

const std::string* Block::getBlockVisual() const
{
	return block_visual;
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

Text::Text(BlockId block_id, Property repr, std::set<Property> property, const std::string& block_visual, Entity* this_entity)
	: Block(block_id, BlockType::TEXT, property, block_visual), this_entity(this_entity), repr(repr)
{

}

Entity* Text::getThisEntity() const
{
	return this_entity;
}

Property Text::getRepr() const
{
	return repr;
}

// CLASS ENTITY PART ======================================

Entity::Entity(BlockId block_id, std::set<Property> property, const std::string& block_visual)
	: Block(block_id, BlockType::ENTITY, property, block_visual)
{

}

const std::vector<Entity::Position>& Entity::getPosition() const {
	return position;
}

void Entity::addPosition(Entity::Position pos) {
	position.push_back(pos);
}

bool Entity::modifyPosition(const Entity::Position& src, Entity::Position dst) {
	if (auto iter = std::find(position.begin(), position.end(), src); iter != position.end())
	{
		*iter = dst;
		return true;
	}
	return false;
}

void Entity::resetPosition() {
	position.clear();
}
