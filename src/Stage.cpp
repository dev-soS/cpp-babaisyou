#include "Stage.hpp"

Stage::Stage(StageName stage_name) 
	: stage(Map<20, 10>()), stage_wrapper(MapWrapper<20, 10>(stage))
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

		
		break;
	case StageName::STAGE1_2:

		break;
	}
}