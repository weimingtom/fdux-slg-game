#include "StringTable.h"

#include "DataLibrary.h"

StringTable::StringTable()
{

}
StringTable::~StringTable()
{

}
std::string StringTable::getString(std::string key)
{
	std::string str;
	bool re = DataLibrary::getSingleton().getData(std::string("GameData/StaticData/StringTable/") + key,str);
	if(re)
		return str;
	return key;
}