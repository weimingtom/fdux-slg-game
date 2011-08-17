#pragma once
#include <ticpp.h>
#include <string>

class StringTable
{
public:
	StringTable();
	~StringTable();

	std::wstring GetString(std::wstring key);
	bool SetString(std::wstring key, std::wstring str);

	int GetNum();

	std::wstring GetKey(int index);
	bool SetKey(std::wstring key, std::wstring newkey);

	void AddString(); 
	void DelString(std::wstring key);
};