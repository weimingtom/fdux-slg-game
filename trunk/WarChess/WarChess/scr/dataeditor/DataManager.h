#pragma once

#include <string>
#include <vector>
#include <ticpp.h>

#include "iisingleton.hpp"
using namespace izayoi;

#define DATAFILE() DataManager::getSingleton().xmlManager_

class SoldierManager;
class HorseManager;
class PWeaponManager;
class SWeaponManager;
class ArmorManager;
class ShieldManager;
class SquadManager;
class StringTable;

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

	SoldierManager* mSoldierManager;
	HorseManager* mHorseManager;
	PWeaponManager* mPWeaponManager;
	SWeaponManager* mSWeaponManager;
	ArmorManager* mArmorManager;
	ShieldManager* mShieldManager;
	StringTable* mStringTable;

	XMLManager* xmlManager_;

private:
	bool CreatModDir(std::wstring dirName); //检查一个文件夹是否存在，不存在则创建
	bool CreatLangDir(std::wstring dirName);

	void SaveData();
	void SaveLang();
	void LoadData();
	void LoadLang();
	bool mEditorMode;
};