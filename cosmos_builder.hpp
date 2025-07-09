#pragma once

#include "cosmos.hpp"

#include <string>
#include <fstream>

class CosmosBuilder
{
public:
	virtual ~CosmosBuilder();

	bool build(Cosmos& cosmos);

protected:
	virtual bool new_life(i64& x, i64& y) = 0;
};

class CosmosFileBuilder : public CosmosBuilder
{
public:
	CosmosFileBuilder(const std::string& file_name);

private:
	virtual bool new_life(i64& x, i64& y) override;

private:
	std::fstream file_;
};

class CosmosStdioBuilder : public CosmosBuilder
{
public:
	CosmosStdioBuilder();

private:
	virtual bool new_life(i64& x, i64& y) override;
};
