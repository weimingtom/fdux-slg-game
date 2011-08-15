#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"

class ShieldManager
{
public:
	ShieldManager();
	~ShieldManager();

	bool LoadMod(std::wstring modName,std::wstring langName, bool editorMode);
	bool LoadLang(std::wstring langName);


	//编辑器用函数
	bool SaveData();
	bool SaveLang();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	std::wstring GetName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetScriptName(std::wstring id);
	//std::wstring GetModuleName(std::wstring id); refactor to GetMeshName(std::wstring id)
	std::wstring GetMeshName(std::wstring id);
	std::wstring GetMatName(std::wstring id);
	int GetValue(std::wstring id);

	void AddShield();
	void DelShield(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	//bool SetModuleName(std::wstring id, std::wstring modulename); refactor to SetMeshName(std::wstring id, std::wstring meshname)
	bool SetMeshName(std::wstring id, std::wstring meshname);
	bool SetMatName(std::wstring id, std::wstring matname);
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