

#include <iostream>

#include "cosmos_builder.hpp"

CosmosBuilder::~CosmosBuilder()
{

}

bool CosmosBuilder::build(Cosmos& cosmos)
{
	i64 x = 0;
	i64 y = 0;

	while (this->new_life(x, y)) {
		cosmos.add_life(x, y);
	}

	return true;
}

CosmosFileBuilder::CosmosFileBuilder(const std::string& file_name)
{
	file_.open(file_name);
	if (!file_.is_open()) {
		std::cout << "unable to open file:[" << file_name << "]" << std::endl;
		return;
	}

	std::string header;
	std::getline(file_, header);
	std::cout << "[file builder]" << header << std::endl;
}

bool CosmosFileBuilder::new_life(i64& x, i64& y)
{
	if (!file_.is_open()) {
		return false;
	}

	if (file_ >> x >> y) {
		return true;
	}

	return false;
}

// stdio builder
CosmosStdioBuilder::CosmosStdioBuilder()
{
	std::string header;
	std::getline(std::cin, header);

	std::cout << "[stdio builder]" << header << std::endl;
}

bool CosmosStdioBuilder::new_life(i64& x, i64& y)
{
	while (std::cin >> x >> y) {
		return true;
	}

	return false;
}