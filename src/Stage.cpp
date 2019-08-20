#include "Stage.hpp"

#include <string>

Stage::Stage(StageName stage_name) 
	: stage(Map<20, 10>())
{
	switch ( stage_name )
	{
	case StageName::STAGE1_1:
		stage[1][1] = &Text::baba;
		stage[1][2] = &Text::is;
		stage[1][3] = &Text::you;

		stage[1][16] = &Text::flag;
		stage[1][17] = &Text::is;
		stage[1][18] = &Text::win;

		stage[5][2] = &Entity::baba;
		stage[5][17] = &Entity::flag;

		stage.update();
		break;
	case StageName::STAGE1_2:

		break;
	}
}

void Stage::gotoxy(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void Stage::printBlock(Block* block, int x, int y)
{
	if ( block == nullptr ) return;
	for ( int i = 0; i < 3; ++i )
	{
		gotoxy(4 * x + 1, 4 * y + i + 1);
		std::cout << block->getBlockVisual()[i];
	}
}


void Stage::printMapOverall()
{
	for (int i = 0; i < 10; ++i )
	{
		for ( int j = 0; j < 20; ++j )
		{
			printBlock(stage[i][j], j, i);
		}
	}
}

void Stage::printMapFrame()
{
	for ( int i = 0; i < 10; ++i )
	{
		std::cout << "---------------------------------------------------------------------------------" << std::endl;
		for ( int j = 0; j < 3; ++j )
		{
			std::cout << "|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |" << std::endl;
		}
	}
	std::cout << "---------------------------------------------------------------------------------" << std::endl;
}