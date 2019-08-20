#include <iostream>

#include "Stage.hpp"

int main()
{
	Stage stage1(StageName::STAGE1_1);
	stage1.printMapFrame();
	stage1.printMapOverall();

	int a;
	std::cin >> a;
}
