#pragma once
#include <ticpp.h>
#include <string>

class StringTable
{
public:
	StringTable();
	~StringTable();

	bool LoadLang(std::wstring langName, bool editorMode);

	std::wstring GetString(std::wstring key);
	bool SetString(std::wstring key, std::wstring str);

	//±à¼­Æ÷ÓÃº¯Êý
	bool SaveData();
	bool SaveLang();

	int GetNum();

	std::wstring GetKey(int index);
	bool SetKey(std::wstring key, std::wstring newkey);

	void AddString(); 
	void DelString(std::wstring key);

private:
	std::string mLangPath;

	ticpp::Document mLangFile;

	bool CreateLangFile();
};