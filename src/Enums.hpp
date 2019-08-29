#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class Property
{
	INVALID,
	ENTITY,
	PUSH,
	YOU,
	WIN,
	STOP
};

enum class MoveType
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

enum class BlockId
{
	BABA,
	FLAG,
	IS,
	YOU,
	WIN,
	PUSH,
	STOP,
};

enum class BlockType
{
	TEXT,
	ENTITY,
};

enum class StageName
{
	BASE_STAGE,
	STAGE1_1,
	STAGE1_2,
};
#endif