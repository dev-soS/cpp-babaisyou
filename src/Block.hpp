#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Enums.hpp"

#include <set>

class Block
{
protected :
	std::set<Property> properties;
	BlockId block_id;
	char block_visual[3][3];

public :
	Block(BlockId block_id, std::set<Property> property, const char* block_visual);
	virtual ~Block(){}

	void addProperty(Property property);
	void addProperty(std::set<Property> property);

	void removeProperty(Property property);
	void removeProperty(const std::set<Property>& property);

	bool containProperty(Property property) const;
	BlockId getBlockId();
};

class Entity : public Block
{
private:

public:
	Entity(BlockId block_id, std::set<Property> property, const char* block_visual);
	~Entity(){}

	static Entity baba;
	static Entity flag;
};

class Text : public Block
{
private :
	Entity* this_entity;

public :
	Text(BlockId block_id, std::set<Property> property, const char* block_visual, Entity* this_entity = nullptr);
	~Text(){}

	static Text baba;
	static Text is;
	static Text you;
	static Text flag;
	static Text win;
	static Text push;
	static Text stop;

	Entity* getThisEntity();
};



#endif