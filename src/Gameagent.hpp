#pragma once
#ifndef GAMEAGENT_HPP
#define GAMEAGENT_HPP

#include "Map.hpp"

class GameManager
{
private:

public:
	static Map stage_1;

	void callGameStage();
	void excuteGame();
};


#endif