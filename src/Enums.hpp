#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class Property
{
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
	BABATEXT,
	FLAGTEXT,
	ISTEXT,
	YOUTEXT,
	WINTEXT,
	PUSHTEXT,
	STOPTEXT,
	BABAENTITY,
	FLAGENTITY,
};
#endif