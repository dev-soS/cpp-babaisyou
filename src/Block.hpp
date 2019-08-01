#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Enums.hpp"
#include <set>

class Block
{
protected :
	std::set<Property> properties;
	std::string block_name;
public :
	Block(std::string name, std::set<Property> property);
	void addProperty(Property property);
	void addProperty(std::set<Property> property);
	void removeProperty(Property property);
	void removeProperty(const std::set<Property>& property);

	bool move(MoveType move_type);
};

class Text : public Block
{
private :

public :
	Text(std::string name, std::set<Property> property);

	static Text baba;
	static Text is;
	static Text you;
	static Text flag;
	static Text win;
	static Text push;
	static Text stop;

};

class Entity : public Block
{
private :

public :
	Entity(std::string name, std::set<Property> property);

	static Entity baba;
	static Entity flag;
};

#endif