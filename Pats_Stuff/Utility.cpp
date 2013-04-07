#include "stdafx.h"
#include "Utility.h"

void split(std::string& target, char delimeter, std::vector<std::string>& elements)
{
	std::stringstream ss(target);
	std::string item;

	while(getline(ss, item, delimeter))
	{
		elements.push_back(item);
	}
}