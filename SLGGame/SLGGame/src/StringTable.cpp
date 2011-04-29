#include "StringTable.h"

#include "DataLibrary.h"
#include "conversion.h"

StringTable::StringTable()
{

}
StringTable::~StringTable()
{

}
std::string StringTable::getString(std::string key)
{
	std::string str;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/StringTable/") + key,str);
	if(re)
		return str;
	return key;
}

std::string StringTable::getAnsiString(std::string key)
{
	std::string str;
	bool re = DataLibrary::getSingleton().getData(std::string("StaticData/StringTable/") + key,str);
	if(re)
	{
		std::wstring tempstring;
		UTF8ToUnicode(str,tempstring);
		UnicodeToANSI(tempstring,str);
		return str;
	}
	return key;
}