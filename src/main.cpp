

#include "cosmos.hpp"
#include "cosmos_builder.hpp"

int main(int argc, const char** argv)
{
	Cosmos cosmos;

	CosmosStdioBuilder builder;

	builder.build(cosmos);

	cosmos.evolve(10);

	builder.dump(cosmos);
}