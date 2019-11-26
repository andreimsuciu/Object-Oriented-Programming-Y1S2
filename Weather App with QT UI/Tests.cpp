#include "Tests.h"

void test()
{
	std::vector<Interval> repo;
	Controller ctrl{ repo };
	int total = ctrl.hours("sunny");
	assert(total == 6);
}
