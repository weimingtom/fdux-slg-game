#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>

class StringTable: public IISingleton<StringTable>
{
public:
	StringTable();
	~StringTable();
	std::string getString(std::string key);
	std::string getAnsiString(std::string key);
private:
};