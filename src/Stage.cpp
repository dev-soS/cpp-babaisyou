#include "Stage.hpp"

#include <string>

Stage::Stage(StageName stage_name) 
{
	switch ( stage_name )
	{
	case StageName::STAGE1_1:
		stage[1][1].push_back(&Text::baba);
		stage[1][2].push_back(&Text::is);
		stage[1][3].push_back(&Text::you);

		stage[1][16].push_back(&Text::flag);
		stage[1][17].push_back(&Text::is);
		stage[1][18].push_back(&Text::you);

		stage[5][2].push_back(&Entity::baba);
		stage[5][17].push_back(&Entity::flag);

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

void Stage::printBlock(const std::vector<Block*>& blocks, int x, int y)
{
	if ( blocks.empty() ) return;
	for ( int i = 0; i < 3; ++i )
	{
		gotoxy(4 * x + 1, 4 * y + i + 1);
		std::cout << blocks.back()->getBlockVisual()[i];
	}
}

void Stage::printMapOverall()
{
	for ( int i = 0; i < 10; ++i )
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