#include "Gameagent.hpp"
#include "Enums.hpp"

#include <Windows.h>
#include <iostream>
#include <conio.h>

void GameManager::gotoxy(int x, int y) // (x,y)로 커서를 옮겨주는 함수
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void GameManager::printBlock(Block* block, int x, int y) const
{
	for (int i = 0; i < 3; ++i )
	{
		gotoxy(3 * x, 3 * y + i);
		for (int j = 0; j < 3; ++j )
		{
			std::cout << block->getBlockVisual()[i][j];
		}
	}
}
void GameManager::printMapPartially(Map<size_t Width, size_t Height>)
{
	
}

StageName GameManager::selectStage()
{
	std::cout << "                           " << std::endl
		<< "      1-1   1-2   1-3      " << std::endl
		<< "                           " << std::endl;

	
	int keyboard = 0;
	while ( keyboard != 13 )
	{
		keyboard = getch();
		switch ( keyboard )
		{
		case 13: // enter
			break;

		case 77: // RIGHT
			break;

		case 75: // LEFT
			break;

		case 72: // UP
			break;

		case 80: // DOWN
			break;
		}
	}
}

Map<Width, Height>* GameManager::makeGameStage(StageName stage_name)
{
	switch ( stage_name )
	{
	case StageName::STAGE1_1:
		return new Map<Width, Height>();
	case StageName::STAGE1_2:

	}
}


//select stage part => make stage for select
//make stage
//print stage

//repeat this
//input keyboard
//implement move()
//implement update()
//select printall or printpart
//check win condition
void GameManager::excuteGame()
{
	
}