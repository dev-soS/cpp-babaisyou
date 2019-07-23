#include "Block.hpp"

Text Text::baba("BABA", { Property::PUSH });
Text Text::is("IS", { Property::PUSH });
Text Text::you("YOU", { Property::PUSH });
Text Text::flag("FLAG", { Property::PUSH });
Text Text::win("WIN", { Property::PUSH });
Text Text::push("PUSH", { Property::PUSH });
Text Text::stop("STOP", { Property::PUSH });

Entity Entity::baba("BABA", {});
Entity Entity::flag("FLAG", {});

// CLASS BLOCK PART =======================================

Block::Block(std::string name, std::set<Property> property)  : block_name(name), properties(property){

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

bool Block::move(MoveType move_type)
{
	switch ( move_type )
	{
	case MoveType::UP :

	case MoveType::DOWN :

	case MoveType::LEFT :

	case MoveType::RIGHT :

	}
}

// CLASS TEXT PART ========================================

Text::Text(std::string name, std::set<Property> property) : Block(name, property)
{

}

// CLASS ENTITY PART ======================================

Entity::Entity(std::string name, std::set<Property> property) : Block(name, property)
{

}
