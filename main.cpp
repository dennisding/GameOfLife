
#include <iostream>

#include "cosmos.hpp"

void test_triangle()
{

}

void check_cosmos(Cosmos& source, Cosmos& result, const char* msg)
{
	if (source == result) {
		std::cout << msg << ": Success" << std::endl;
	}
	else {
		std::cout << msg << ": Failed" << std::endl;
	}
}

void evolve(Cosmos& cosmos, int step)
{
	for (int i = 0; i < step; ++i) {
		cosmos.evolve();
	}
}

void test_death()
{
	Cosmos cosmos;
	cosmos.add_life(0, 0);
	evolve(cosmos, 1);

	Cosmos result;
	check_cosmos(cosmos, result, "check death");
}

void test_spawn()
{
	Cosmos cosmos;
	Cosmos result;

	cosmos.add_life(0, 0);
	cosmos.add_life(0, 1);
	cosmos.add_life(1, 1);
	evolve(cosmos, 1);

	result.add_life(0, 0);
	result.add_life(0, 1);
	result.add_life(1, 1);
	result.add_life(1, 0);

	check_cosmos(cosmos, result, "check spawn");

	evolve(cosmos, 100);
	check_cosmos(cosmos, result, "check spawn and static");
}

void do_test()
{
	test_death();
	test_spawn();
}

int main(int argc, const char** argv)
{
	do_test();
	//Cosmos cosmos;

	//cosmos.add_life(0, 0);
	//cosmos.add_life(0, 1);
	//cosmos.add_life(1, 1);
	////cosmos.add_life(0, 1);
	////cosmos.add_life(1, 2);
	////cosmos.add_life(2, 0);
	////cosmos.add_life(2, 1);
	////cosmos.add_life(2, 2);
	////cosmos.add_life(-2000000000000, -2000000000000);
	////cosmos.add_life(-2000000000001, -2000000000001);
	////cosmos.add_life(-2000000000000, -2000000000001);

	//while (!cosmos.heat_death()) {
	//	int generation = cosmos.evolve();
	//	std::cout << "evolve generation:" << generation << std::endl;
	//}
}