#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"

class Horse;

class HorseManager
{
public:
	HorseManager();
	~HorseManager();

	bool LoadMod(std::wstring modName,std::wstring langName, bool editorMode);
	bool LoadLang(std::wstring langName);

	Horse* GetHorse(std::wstring id);

	//编辑器用函数
	bool SaveData();
	bool SaveLang();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetName(std::wstring id);
	std::wstring GetScriptName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetValue(std::wstring id);

	void AddHorse(); 
	void DelHorse(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	bool SetValue(std::wstring id, int ivalue);

private:

	std::wstring mModPath;
	std::string mDataPath;
	std::string mLangPath;

	ticpp::Document mDataFile;
	ticpp::Document mLangFile;

	bool CreateDataFile();
	bool CreateLangFile();
};