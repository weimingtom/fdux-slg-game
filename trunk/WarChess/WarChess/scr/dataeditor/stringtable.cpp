#include "stringtable.h"
#include "DataManager.h"
#include "XMLManager.h"
#include "conversion.h"
#include <Windows.h>

StringTable::StringTable()
{

}

StringTable::~StringTable()
{

}

void StringTable::AddString()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newstringkey%d",n);
	while(DATAFILE()->GetStringTable(newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newstringkey%d",n);
	}

	ticpp::Element *newStringElement = new ticpp::Element(newid);
	newStringElement->SetAttribute("type", "String");
	newStringElement->SetAttribute("value", "String");
	DATAFILE()->AddStringTable(newStringElement);
}

void StringTable::DelString(std::wstring _key)
{
	std::string tempkey;
	UnicodeToUTF8(_key,tempkey);
	DATAFILE()->RemoveStringTable(tempkey);
}

int StringTable::GetNum()
{
	return DATAFILE()->CountStringTable();
}

std::wstring StringTable::GetKey(int _index)
{
	return DATAFILE()->GetStringTableID(_index);
}

bool StringTable::SetKey(std::wstring _key, std::wstring _newkey)
{
	std::string tempkey;
	UnicodeToUTF8(_key,tempkey);
	std::string tempnewkey;
	UnicodeToUTF8(_newkey,tempnewkey);
	ticpp::Element * element = DATAFILE()->GetStringTable(tempnewkey);
	if (element == NULL)
	{
		DATAFILE()->SetStringTableID(tempkey, tempnewkey);
	}
	return true;
}

std::wstring StringTable::GetString(std::wstring _key)
{
	std::string tempkey;
	UnicodeToUTF8(_key, tempkey);
	ticpp::Element *stringElement = DATAFILE()->GetStringTable(tempkey);
	std::string tempString;
	tempString = stringElement->GetAttribute("value");
	std::wstring stringValue;
	UTF8ToUnicode(tempString, stringValue);
	return stringValue;
}

bool StringTable::SetString(std::wstring _key, std::wstring _str)
{
	std::string tempkey;
	UnicodeToUTF8(_key, tempkey);
	std::string tempstr;
	UnicodeToUTF8(_str, tempstr);
	DATAFILE()->SetStringTable(tempkey, tempstr);
	return true;
}