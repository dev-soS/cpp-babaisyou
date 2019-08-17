#pragma once
#ifndef STAGE_HPP
#define STAGE_HPP

#include "Map.hpp"
#include "MapWarpper.hpp"

class Stage
{
private:
	Map<20, 10> stage;
	MapWrapper<20, 10> stage_wrapper;
public:
	Stage(StageName stage_name);
};
#endif