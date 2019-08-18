#pragma once
#ifndef STAGE_HPP
#define STAGE_HPP

#include "Map.hpp"
#include "MapWarpper.hpp"

#include <Windows.h>

class Stage
{
private:
	Map<20, 10> stage;
public:
	Stage(StageName stage_name);
	void gotoxy(int x, int y);
	void printBlock(Block* block, int x, int y) const;
	void printMapOverall() const;
	void printMapPartially(std::tuple<size_t, size_t> pos, MoveType direction, size_t cnt) const;
};
#endif