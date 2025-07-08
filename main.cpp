
#include <iostream>

#include "cosmos.hpp"

int main(int argc, const char** argv)
{
	Cosmos cosmos;

	//cosmos.add_life(0, 0);
	//cosmos.add_life(0, 1);
	//cosmos.add_life(1, 1);
	//cosmos.add_life(0, 1);
	//cosmos.add_life(1, 2);
	//cosmos.add_life(2, 0);
	//cosmos.add_life(2, 1);
	//cosmos.add_life(2, 2);
	cosmos.add_life(-2000000000000, -2000000000000);
	cosmos.add_life(-2000000000001, -2000000000001);
	cosmos.add_life(-2000000000000, -2000000000001);

	while (!cosmos.head_death()) {
		int generation = cosmos.evolve();
		std::cout << "evolve generation:" << generation << std::endl;
	}
}