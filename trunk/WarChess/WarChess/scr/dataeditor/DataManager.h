#pragma once

#include <string>
#include <vector>
#include <ticpp.h>
#include "Modifier.h"
#include "DataTag.h"

#include "iisingleton.hpp"
using namespace izayoi;

#define DATAMANAGER() DataManager::getSingleton()

//class SoldierManager;
//class HorseManager;
//class PWeaponManager;
//class SWeaponManager;
//class ArmorManager;
//class ShieldManager;
//class SquadManager;
//class StringTable;

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

	//SoldierManager* mSoldierManager;
	//HorseManager* mHorseManager;
	//PWeaponManager* mPWeaponManager;
	//SWeaponManager* mSWeaponManager;
	//ArmorManager* mArmorManager;
	//ShieldManager* mShieldManager;
	//StringTable* mStringTable;

	XMLManager* xmlManager_;

	void AddArmor();
	void AddHorse();
	void AddPrimaryWeapon();
	void AddSecondaryWeapon();
	void AddShield();
	void AddSoldier();
	void AddString();

	void RemoveData(std::string _parent, std::wstring _id);
	void RemoveStrTable(std::wstring _key);

	int GetCount(std::string _parent);
	int GetStrTableCount();
	int GetInt(std::string _parent, std::wstring _id, std::string _tag);
	int GetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType);

	std::wstring GetID(std::string _parent, int _index);
	std::wstring GetStrTableID(int _index);
	std::wstring GetLangStr(std::string _parent, std::wstring _id, std::string _tag);
	std::wstring GetDataStr(std::string _parent, std::wstring _id, std::string _tag);
	std::wstring GetStrTable(std::wstring _key);

	bool SetInt(std::string _parent, std::wstring _id, std::string _tag, int _value);
	bool SetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType, int _attr);

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