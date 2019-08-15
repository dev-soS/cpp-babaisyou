#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Enums.hpp"

#include <set>

class Block
{
protected:
	std::set<Property> properties;
	BlockId block_id;
	BlockType block_type;
	char block_visual[3][3];

public:
	Block(BlockId block_id, BlockType block_type, std::set<Property> property, const char* block_visual);
	virtual ~Block(){}

	void addProperty(Property property);
	void addProperty(std::set<Property> property);

	void removeProperty(Property property);
	void removeProperty(const std::set<Property>& property);

	const std::set<Property>& getProperties() const;
	bool containProperty(Property property) const;

	BlockId getBlockId() const;
	BlockType getBlockType() const;
};

class Entity : public Block
{
private:
	std::vector<std::tuple<size_t, size_t>> position;

public:
	Entity(BlockId block_id, std::set<Property> property, const char* block_visual);
	~Entity(){}

	const std::vector<std::tuple<size_t, size_t>>& getPosition() const;
	void addPosition(std::tuple<size_t, size_t> pos);
	bool modifyPosition(const std::tuple<size_t, size_t>& src, std::tuple<size_t, size_t> dst);
	void resetPosition();

	static Entity baba;
	static Entity flag;
};

class Text : public Block
{
private:
	Entity* this_entity;
	Property repr;

public:
	Text(BlockId block_id, Property repr, std::set<Property> property, const char* block_visual, Entity* this_entity = nullptr);
	~Text(){}

	Entity* getThisEntity() const;
	Property getRepr() const;

	static Text baba;
	static Text is;
	static Text you;
	static Text flag;
	static Text win;
	static Text push;
	static Text stop;
};

#endif