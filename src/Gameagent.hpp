#pragma once
#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "Map.hpp"

template<size_t Width, size_t Height>
class GameManager
{
private:
	void gotoxy(int x, int y);
	void printBlock(Block* block, int x, int y) const;
	void printMapPartially(Map<Width, Height> stage) const;
	void printMapOverall(Map<Width, Height> stage) const;
public:

	StageName selectStage();
	Map<Width, Height>* makeGameStage(Map<Width, Height> stage);
	void excuteGame();
};

#endif