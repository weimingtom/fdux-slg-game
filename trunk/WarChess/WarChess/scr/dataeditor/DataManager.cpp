#include "DataManager.h"
#include "soldiermanager.h"
#include "horsemanager.h"
#include "pweaponmanager.h"
#include "sweaponmanager.h"
#include "armormanager.h"
#include "shieldmanager.h"
#include "stringtable.h"
#include "XMLManager.h"

#include <Windows.h>
#include <string.h>
#include <algorithm>

DataManager::DataManager(bool editormode)
{
	mEditorMode = editormode;
	mStringTable = new StringTable();
	mSoldierManager = new SoldierManager();
	mHorseManager = new HorseManager();
	mPWeaponManager = new PWeaponManager();
	mSWeaponManager = new SWeaponManager();
	mArmorManager = new ArmorManager();
	mShieldManager = new ShieldManager();

	xmlManager_ = new XMLManager();
	
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));

	std::wstring dirName;
	dirName = L".\\..\\Mod\\*";

	//检查MOD目录
	hFind = FindFirstFile(dirName.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			wcscmp(findFileData.cFileName,L".") && 
			wcscmp(findFileData.cFileName,L".."))
		{
			_wcslwr_s(findFileData.cFileName,wcslen(findFileData.cFileName)+1);
			mModList.push_back(findFileData.cFileName);
		}
		while (FindNextFile(hFind, &findFileData) != 0) 
		{
			if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				wcscmp(findFileData.cFileName,L".") && 
				wcscmp(findFileData.cFileName,L".."))
			{
				_wcslwr_s(findFileData.cFileName,wcslen(findFileData.cFileName)+1);
				mModList.push_back(findFileData.cFileName);
			}
		}
		FindClose(hFind);
	}

	ChangeMod(L"common");
}

DataManager::~DataManager()
{
	
}

bool DataManager::CreatModDir(std::wstring dirName)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));
	std::wstring path = L".\\..\\Mod";
	hFind = FindFirstFile(path.c_str(), &findFileData);
	bool result;
	if(hFind == INVALID_HANDLE_VALUE)
	{
		result = CreateDirectory(path.c_str() ,  NULL);
		if(!result)
			return false;
	}
	else
		FindClose(hFind);

	path = path + L"\\" + dirName;
	hFind = FindFirstFile(path.c_str(), &findFileData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		result = CreateDirectory(path.c_str() ,  NULL);
		if(!result)
			return false;
		mModList.push_back(dirName);
	}
	else
		FindClose(hFind);
	
	path = path + L"\\Data";
	hFind = FindFirstFile(path.c_str(), &findFileData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		result = CreateDirectory(path.c_str() ,  NULL);
		if(!result)
			return false;
	}
	else
		FindClose(hFind);

	path = path + L"\\..\\Lang";
	hFind = FindFirstFile(path.c_str(), &findFileData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		result = CreateDirectory(path.c_str() ,  NULL);
		if(!result)
			return false;
	}
	else
		FindClose(hFind);

	return true;
}

bool DataManager::CreatLangDir(std::wstring dirName)
{
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));
	std::wstring path = L".\\..\\Mod\\" + *mCurMod + L"\\Lang\\" + dirName;
	hFind = FindFirstFile(path.c_str(), &findFileData);
	bool result = false;
	if(hFind == INVALID_HANDLE_VALUE)
	{
		result = CreateDirectory(path.c_str() ,  NULL);
		if(!result)
			return false;
		mLangList.push_back(dirName);
	}
	else
		FindClose(hFind);

	return true;
}

bool DataManager::ChangeMod(std::wstring mod)
{
	if(mEditorMode)
		SaveData();
	//检查是否存在文件夹，没有则创建
	CreatModDir(mod);
	mCurMod = std::find(mModList.begin(),mModList.end(),mod);

	//遍历语言文件夹
	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));

	mLangList.clear();
	std::wstring dirName;
	dirName = L".\\..\\Mod\\" + *mCurMod + L"\\Lang\\*";
	hFind = FindFirstFile(dirName.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) 
	{
		if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			wcscmp(findFileData.cFileName,L".") && 
			wcscmp(findFileData.cFileName,L".."))
		{
			_wcslwr_s(findFileData.cFileName,wcslen(findFileData.cFileName)+1);
			mLangList.push_back(findFileData.cFileName);
		}
		while (FindNextFile(hFind, &findFileData) != 0) 
		{
			if((findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				wcscmp(findFileData.cFileName,L".") && 
				wcscmp(findFileData.cFileName,L".."))
			{
				_wcslwr_s(findFileData.cFileName,wcslen(findFileData.cFileName)+1);
				mLangList.push_back(findFileData.cFileName);
			}
		}
		FindClose(hFind);
	}

	if(mLangList.size() == 0)
		CreatLangDir(L"chinese");
	mCurLang = std::find(mLangList.begin(),mLangList.end(),L"chinese");
	
	LoadData();
	return true;
}

bool DataManager::ChangeLang(std::wstring lang)
{
	if(mEditorMode)
		SaveLang();
	CreatLangDir(lang);
	mCurLang = std::find(mLangList.begin(),mLangList.end(),lang);
	LoadLang();
	return true;
}

void DataManager::SwitchEditorMode(bool editormode)
{
	if(mEditorMode == true && editormode == false)
	{
		mEditorMode = editormode;
		SaveData();
		LoadData();
	}
	else if(mEditorMode == false && editormode == true)
	{
		mEditorMode = editormode;
		LoadData();
	}
}

void DataManager::SaveData()
{
	//mSoldierManager->SaveData();
	//mHorseManager->SaveData();
	//mPWeaponManager->SaveData();
	//mSWeaponManager->SaveData();
	//mArmorManager->SaveData();
	//mShieldManager->SaveData();
	//SaveLang();

	xmlManager_->SaveData();
	xmlManager_->SaveLang();
	xmlManager_->SaveStringTable();
}

void DataManager::SaveLang()
{
	//mStringTable->SaveLang();
	//mSoldierManager->SaveLang();
	//mHorseManager->SaveLang();
	//mPWeaponManager->SaveLang();
	//mSWeaponManager->SaveLang();
	//mArmorManager->SaveLang();
	//mShieldManager->SaveLang();

	xmlManager_->SaveLang();
	xmlManager_->SaveStringTable();
}

void DataManager::LoadData()
{
	//mSoldierManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mHorseManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mPWeaponManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mSWeaponManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mArmorManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mShieldManager->LoadMod(*mCurMod,*mCurLang,mEditorMode);
	//mStringTable->LoadLang(*mCurLang,mEditorMode);

	xmlManager_->LoadMod(*mCurMod, *mCurLang, mEditorMode);
}

void DataManager::LoadLang()
{
	//mStringTable->LoadLang(*mCurLang,mEditorMode);
	//mSoldierManager->LoadLang(*mCurLang);
	//mHorseManager->LoadLang(*mCurLang);
	//mPWeaponManager->LoadLang(*mCurLang);
	//mSWeaponManager->LoadLang(*mCurLang);
	//mArmorManager->LoadLang(*mCurLang);
	//mShieldManager->LoadLang(*mCurLang);

	xmlManager_->LoadLang(*mCurMod, *mCurLang, mEditorMode);
}