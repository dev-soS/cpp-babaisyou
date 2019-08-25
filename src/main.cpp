#include <iostream>

#include "Stage.hpp"

int main()
{
	Stage stage1(StageName::STAGE1_1);
	stage1.printMapFrame();

	int a;
	std::cin >> a;


	stage1.printMapOverall();
	stage1.printMapOverall();
	stage1.printMapOverall();
}
