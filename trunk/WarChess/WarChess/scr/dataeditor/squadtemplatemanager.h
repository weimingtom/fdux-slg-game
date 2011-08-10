#pragma once
#include <ticpp.h>
#include <string>

class SquadTemplateManager
{
public:
	SquadTemplateManager();
	~SquadTemplateManager();

	bool LoadMod(std::wstring modName,std::wstring langName, bool editorMode);
	bool LoadLang(std::wstring langName);

	//±à¼­Æ÷ÓÃº¯Êý
	bool SaveData();
	bool SaveLang();

private:
	std::wstring mModPath;
	std::string mDataPath;
	std::string mLangPath;

	ticpp::Document mDataFile;
	ticpp::Document mLangFile;

	bool CreateDataFile();
	bool CreateLangFile();
};