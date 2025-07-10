#pragma once

#include "cosmos.hpp"

#include <string>
#include <fstream>

class CosmosBuilder
{
public:
	virtual ~CosmosBuilder();

	bool build(Cosmos& cosmos);
	virtual bool dump(Cosmos& cosmos) = 0;

protected:
	virtual bool new_life(i64& x, i64& y) = 0;
};

class CosmosFileBuilder : public CosmosBuilder
{
public:
	CosmosFileBuilder(const std::string& file_name);

	virtual bool dump(Cosmos& cosmos) override;

private:
	virtual bool new_life(i64& x, i64& y) override;

private:
	std::fstream file_;
};

class CosmosStdioBuilder : public CosmosBuilder
{
public:
	CosmosStdioBuilder();

	virtual bool dump(Cosmos& cosmos) override;

private:
	virtual bool new_life(i64& x, i64& y) override;
};
