#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Enums.hpp"

#include <set>
#include <vector>
#include <tuple>
#include <string>

class Block
{
protected:
	std::set<Property> properties;
	BlockId block_id;
	BlockType block_type;
	std::string block_visual[3];

public:
	Block(BlockId block_id, BlockType block_type, std::set<Property> property, const std::string& block_visual);
	virtual ~Block(){}

	void addProperty(Property property);
	void addProperty(std::set<Property> property);

	void removeProperty(Property property);
	void removeProperty(const std::set<Property>& property);

	const std::set<Property>& getProperties() const;
	bool containProperty(Property property) const;

	const std::string* getBlockVisual() const;
	BlockId getBlockId() const;
	BlockType getBlockType() const;
};

class Entity : public Block
{
public:
	using Position = std::tuple<size_t, size_t, size_t>;

private:
	std::vector<Position> position;

public:
	Entity(BlockId block_id, std::set<Property> property, const std::string& block_visual);
	~Entity(){}

	const std::vector<Position>& getPosition() const;
	void addPosition(Position pos);
	bool modifyPosition(const Position& src, Position dst);
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
	Text(BlockId block_id, Property repr, std::set<Property> property, const std::string& block_visual, Entity* this_entity = nullptr);
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