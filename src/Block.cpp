#include "Block.hpp"

Text Text::baba("BABA", { Property::PUSH }, "B A   B A", &Entity::baba);
Text Text::is("IS", { Property::PUSH }, "   I S   ");
Text Text::you("YOU", { Property::PUSH }, "   YOU   ");
Text Text::flag("FLAG", { Property::PUSH }, "F L   A G", &Entity::flag);
Text Text::win("WIN", { Property::PUSH }, "   WIN   ");
Text Text::push("PUSH", { Property::PUSH }, "P U   S H");
Text Text::stop("STOP", { Property::PUSH }, "S T   O P");

Entity Entity::baba("BABA", {}, "/  OOOO O");
Entity Entity::flag("FLAG", {}, " |> | ===");

// CLASS BLOCK PART =======================================

Block::Block(std::string name, std::set<Property> property, char block_visual[10]) : block_name(name), properties(property)
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
	
// CLASS TEXT PART ========================================

Text::Text(std::string name, std::set<Property> property, char block_visual[10], Entity* this_entity) : Block(name, property, block_visual), this_entity(this_entity)
{

}

Entity* Text::getThisEntity()
{
	return this_entity;
}

// CLASS ENTITY PART ======================================

Entity::Entity(std::string name, std::set<Property> property, char block_visual[10]) : Block(name, property, block_visual)
{

}
