#pragma once

#include <string>
#include <vector>
#include <ticpp.h>
#include "Modifier.h"
#include "DataTag.h"

#include "iisingleton.hpp"
using namespace izayoi;

#define DATAMANAGER() DataManager::getSingleton()

class XMLManager;

class DataManager:public IISingleton<DataManager>
{
public:
	DataManager(bool editormode);
	~DataManager();

	std::vector<std::wstring> mModList;
	std::vector<std::wstring> mLangList;

	typedef std::vector<std::wstring>::iterator DirIter;

	DirIter mCurMod;
	DirIter mCurLang;

	bool ChangeMod(std::wstring mod);
	bool ChangeLang(std::wstring lang);

	void SwitchEditorMode(bool editormode);

	XMLManager* xmlManager_;

	void AddArmor();
	void AddHorse();
	void AddPrimaryWeapon();
	void AddSecondaryWeapon();
	void AddShield();
	void AddSoldier();
	void AddSkill();
	void AddEffect();
	void AddSquad();
	void AddSquadSkill(std::wstring _squadId, std::wstring _skillId);
	void AddString();

	void RemoveData(std::string _parent, std::wstring _id);
	void RemoveSquadSkill(std::wstring _squadId, std::wstring _skillId);
	void RemoveStrTable(std::wstring _key);

	int GetCount(std::string _parent);
	int GetStrTableCount();
	int GetInt(std::string _parent, std::wstring _id, std::string _tag);
	int GetIsSquadSkill(std::wstring _squadId, std::wstring _skillId);
	float GetFloat(std::string _parent, std::wstring _id, std::string _tag);
	float GetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType);

	std::wstring GetID(std::string _parent, int _index);
	std::wstring GetStrTableID(int _index);
	std::wstring GetLangStr(std::string _parent, std::wstring _id, std::string _tag);
	std::wstring GetDataStr(std::string _parent, std::wstring _id, std::string _tag);
	std::wstring GetStrTable(std::wstring _key);

	bool SetInt(std::string _parent, std::wstring _id, std::string _tag, int _value);
	bool SetIsSquadSkill(std::wstring _squadId, std::wstring _skillId, int _value);
	bool SetFloat(std::string _parent, std::wstring _id, std::string _tag, float _value);
	bool SetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType, float _attr);

	bool SetID(std::string _parent, std::wstring _oldID, std::wstring _newID);
	bool SetStrTableID(std::wstring _oldKey, std::wstring _newKey);
	bool SetLangStr(std::string _parent, std::wstring _id, std::string _tag, std::wstring _value);
	bool SetDataStr(std::string _parent, std::wstring _id, std::string _tag, std::wstring _value);
	bool SetStrTable(std::wstring _key, std::wstring _value);

private:
	bool CreatModDir(std::wstring dirName); //检查一个文件夹是否存在，不存在则创建
	bool CreatLangDir(std::wstring dirName);

	void SaveData();
	void SaveLang();
	void LoadData();
	void LoadLang();
	bool mEditorMode;	
};