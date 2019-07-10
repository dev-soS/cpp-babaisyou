#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Property.hpp"
#include <vector>

class Block
{
protected :
	std::vector<Property> properties;
	std::string block_name;
public :
	Block();
};

class Text : public Block
{
private :

public :
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
	static Entity baba;
	static Entity flag;
};

#endif