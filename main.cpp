
#include <iostream>

#include "cosmos.hpp"

void test_triangle()
{

}

void check_cosmos(Cosmos& source, Cosmos& result, const char* msg)
{
	if (source == result) {
		std::cout << "[cosmos]" << msg << ": Success" << std::endl;
	}
	else {
		std::cout << msg << "[cosmos]"  << ": Failed" << std::endl;
	}
}

void check_death(Cosmos& cosmos, Life life, const char* msg)
{
	if (!cosmos.is_alive(life)) {
		std::cout << "[death]" << msg << ": Success" << std::endl;
	}
	else
	{
		std::cout << "[death]" << msg << ": Failed" << std::endl;
	}
}

void check_alive(Cosmos& cosmos, Life life, const char* msg)
{
	if (cosmos.is_alive(life)) {
		std::cout << "[alive]" << msg << ": Success" << std::endl;
	}
	else
	{
		std::cout << "[alive]" << msg << ": Failed" << std::endl;
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
	check_cosmos(cosmos, result, "test death0");

	cosmos.reset();
	cosmos.add_life(0, 0);
	cosmos.add_life(0, 1);
	evolve(cosmos, 1);
	check_cosmos(cosmos, result, "test death1");

	cosmos.reset();
	cosmos.add_life(0, 0);
	cosmos.add_life(1, 1);
	cosmos.add_life(1, -1);
	evolve(cosmos, 1);
	check_alive(cosmos, Life(0, 0), "test alive2");

	cosmos.reset();
	cosmos.add_life(0, 0);
	cosmos.add_life(1, 1);
	cosmos.add_life(-1, -1);
	cosmos.add_life(1, -1);
	cosmos.add_life(-1, 1);

	evolve(cosmos, 1);
	Life new_life(0, 0);
	check_death(cosmos, new_life, "test death5");
//	check_cosmos(cosmos, result, "test death4");
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

	check_cosmos(cosmos, result, "test spawn");

	evolve(cosmos, 100);
	check_cosmos(cosmos, result, "test spawn and static");
}

void test_evolve()
{
	Cosmos cosmos;
	Cosmos result;

	cosmos.add_life(0, 1);
	cosmos.add_life(1, 2);
	cosmos.add_life(2, 0);
	cosmos.add_life(2, 1);
	cosmos.add_life(2, 2);
	
	cosmos.add_life(-2000000000000, -2000000000000);
	cosmos.add_life(-2000000000001, -2000000000001);
	cosmos.add_life(-2000000000000, -2000000000001);

	evolve(cosmos, 1);
	result.add_life(1, 0);
	result.add_life(1, 2);
	result.add_life(2, 1);
	result.add_life(2, 2);
	result.add_life(3, 1);

	result.add_life(-2000000000000, -2000000000000);
	result.add_life(-2000000000001, -2000000000001);
	result.add_life(-2000000000000, -2000000000001);
	result.add_life(-2000000000001, -2000000000000);

	check_cosmos(cosmos, result, "test evolve");
}

void test()
{
	Cosmos cosmos;
	Cosmos result;

	cosmos.add_life(0, 0);
	cosmos.add_life(-1, -1);
	cosmos.add_life(0, -1);

	evolve(cosmos, 1);

	result.add_life(0, 0);
	result.add_life(-1, -1);
	result.add_life(0, -1);
	result.add_life(-1, 0);

	check_cosmos(cosmos, result, "test evolve");
}

void do_test()
{
	test_death();
	test_spawn();
	test_evolve();
	//test();
}

int main(int argc, const char** argv)
{
	do_test();
}