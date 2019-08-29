#ifndef STAGE_HPP
#define STAGE_HPP

#include "Map.hpp"

#include <Windows.h>
#include <iostream>

class Stage
{
private:
	Map<20, 10> stage;
public:
	Stage(StageName stage_name);
	void gotoxy(int x, int y);
	void printBlock(const std::vector<Block*>& blocks, int x, int y);
	void printMapOverall();
	void printMapFrame();
};
#endif