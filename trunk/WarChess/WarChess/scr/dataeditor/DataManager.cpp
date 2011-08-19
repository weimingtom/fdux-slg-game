#include "DataManager.h"
#include "Conversion.h"
#include "XMLManager.h"

#include <Windows.h>
#include <string.h>
#include <algorithm>

DataManager::DataManager(bool editormode)
{
	mEditorMode = editormode;

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
	xmlManager_->SaveData();
	xmlManager_->SaveLang();
	xmlManager_->SaveStringTable();
}

void DataManager::SaveLang()
{
	xmlManager_->SaveLang();
	xmlManager_->SaveStringTable();
}

void DataManager::LoadData()
{
	xmlManager_->LoadMod(*mCurMod, *mCurLang, mEditorMode);
}

void DataManager::LoadLang()
{
	xmlManager_->LoadLang(*mCurMod, *mCurLang, mEditorMode);
}

void DataManager::AddArmor()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newarmor%d", n);
	while(xmlManager_->GetData("ArmorData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newarmor%d",n);
	}
	
	ticpp::Element *newArmorElement = new ticpp::Element(newid);

	ticpp::Element *typeElement = new ticpp::Element("Type");
	ticpp::Element *valueElement = new ticpp::Element("Value");
	ticpp::Element *scriptElement = new ticpp::Element("Script");
	ticpp::Element *attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element *attrTypeElement = new ticpp::Element("Type");
	ticpp::Element *attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element *attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element *attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element *attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element *attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element *attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element *attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element *attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element *attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element *attrConterElement = new ticpp::Element("Conter");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newArmorElement->LinkEndChild(typeElement);
	newArmorElement->LinkEndChild(valueElement);
	newArmorElement->LinkEndChild(scriptElement);
	newArmorElement->LinkEndChild(attrElement);

	xmlManager_->AddData("ArmorData", newArmorElement);

	ticpp::Element *newArmorLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newArmorLangElement->LinkEndChild(nameElement);
	newArmorLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("ArmorData", newArmorLangElement);
}

void DataManager::AddHorse()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newhorse%d",n);
	while(xmlManager_->GetData("HorseData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newhorse%d",n);
	}

	ticpp::Element *newHorseElement = new ticpp::Element(newid);

	ticpp::Element * typeElement = new ticpp::Element("Type");
	ticpp::Element * valueElement = new ticpp::Element("Value");
	ticpp::Element * scriptElement = new ticpp::Element("Script");
	ticpp::Element * attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element * attrTypeElement = new ticpp::Element("Type");
	ticpp::Element * attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element * attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element * attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element * attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element * attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element * attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element * attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element * attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element * attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element * attrConterElement = new ticpp::Element("Conter");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newHorseElement->LinkEndChild(typeElement);
	newHorseElement->LinkEndChild(valueElement);
	newHorseElement->LinkEndChild(scriptElement);
	newHorseElement->LinkEndChild(attrElement);

	xmlManager_->AddData("HorseData", newHorseElement);

	ticpp::Element *newHorseLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newHorseLangElement->LinkEndChild(nameElement);
	newHorseLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("HorseData", newHorseLangElement);
}

void DataManager::AddPrimaryWeapon()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newpweapon%d", n);
	while(xmlManager_->GetData("PweaponData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newpweapon%d",n);
	}
	
	ticpp::Element *newPWeaponElement = new ticpp::Element(newid);
	
	ticpp::Element * typeElement = new ticpp::Element("Type");
	ticpp::Element * valueElement = new ticpp::Element("Value");
	ticpp::Element * scriptElement = new ticpp::Element("Script");
	ticpp::Element * meshElement = new ticpp::Element("Mesh");
	ticpp::Element * matElement = new ticpp::Element("Mat");
	ticpp::Element * aniElement = new ticpp::Element("AniGroup");
	ticpp::Element * attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element * attrTypeElement = new ticpp::Element("Type");
	ticpp::Element * attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element * attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element * attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element * attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element * attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element * attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element * attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element * attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element * attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element * attrConterElement = new ticpp::Element("Conter");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");
	meshElement->SetAttribute("type", "String");
	meshElement->SetAttribute("value", "none");
    matElement->SetAttribute("type", "String");
	matElement->SetAttribute("value", "none");
	aniElement->SetAttribute("type", "String");
	aniElement->SetAttribute("value", "none");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newPWeaponElement->LinkEndChild(typeElement);
	newPWeaponElement->LinkEndChild(valueElement);
	newPWeaponElement->LinkEndChild(scriptElement);
	newPWeaponElement->LinkEndChild(meshElement);
	newPWeaponElement->LinkEndChild(matElement);
	newPWeaponElement->LinkEndChild(aniElement);
	newPWeaponElement->LinkEndChild(attrElement);

	xmlManager_->AddData("PweaponData", newPWeaponElement);

	ticpp::Element *newPWeaponLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newPWeaponLangElement->LinkEndChild(nameElement);
	newPWeaponLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("PweaponData", newPWeaponLangElement);
}

void DataManager::AddSecondaryWeapon()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newsweapon%d", n);
	while(xmlManager_->GetData("SweaponData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newsweapon%d",n);
	}
	
	ticpp::Element *newSWeaponElement = new ticpp::Element(newid);

	ticpp::Element * typeElement = new ticpp::Element("Type");
	ticpp::Element * valueElement = new ticpp::Element("Value");
	ticpp::Element * scriptElement = new ticpp::Element("Script");
	ticpp::Element * meshElement = new ticpp::Element("Mesh");
	ticpp::Element * matElement = new ticpp::Element("Mat");
	ticpp::Element * maxRangeElement = new ticpp::Element("MaxRange");
	ticpp::Element * minRangeElement = new ticpp::Element("MinRange");
	ticpp::Element * aniElement = new ticpp::Element("AniGroup");
	ticpp::Element * attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element * attrTypeElement = new ticpp::Element("Type");
	ticpp::Element * attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element * attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element * attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element * attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element * attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element * attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element * attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element * attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element * attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element * attrConterElement = new ticpp::Element("Conter");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");
	meshElement->SetAttribute("type", "String");
	meshElement->SetAttribute("value", "none");
    matElement->SetAttribute("type", "String");
	matElement->SetAttribute("value", "none");
	maxRangeElement->SetAttribute("type", "Int");
	maxRangeElement->SetAttribute("value", "0");
	minRangeElement->SetAttribute("type", "Int");
	minRangeElement->SetAttribute("value", "0");
	aniElement->SetAttribute("type", "String");
	aniElement->SetAttribute("value", "none");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newSWeaponElement->LinkEndChild(typeElement);
	newSWeaponElement->LinkEndChild(valueElement);
	newSWeaponElement->LinkEndChild(scriptElement);
	newSWeaponElement->LinkEndChild(meshElement);
	newSWeaponElement->LinkEndChild(matElement);
	newSWeaponElement->LinkEndChild(maxRangeElement);
	newSWeaponElement->LinkEndChild(minRangeElement);
	newSWeaponElement->LinkEndChild(aniElement);
	newSWeaponElement->LinkEndChild(attrElement);

	xmlManager_->AddData("SweaponData", newSWeaponElement);

	ticpp::Element *newSWeaponLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newSWeaponLangElement->LinkEndChild(nameElement);
	newSWeaponLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("SweaponData", newSWeaponLangElement);
}

void DataManager::AddShield()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newshield%d", n);
	while(xmlManager_->GetData("ShieldData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newshield%d",n);
	}
	
	ticpp::Element *newShieldElement = new ticpp::Element(newid);

	ticpp::Element * valueElement = new ticpp::Element("Value");
	ticpp::Element * scriptElement = new ticpp::Element("Script");
	ticpp::Element * meshElement = new ticpp::Element("Mesh");
	ticpp::Element * matElement = new ticpp::Element("Mat");
	ticpp::Element * attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element * attrTypeElement = new ticpp::Element("Type");
	ticpp::Element * attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element * attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element * attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element * attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element * attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element * attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element * attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element * attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element * attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element * attrConterElement = new ticpp::Element("Conter");

	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");
	meshElement->SetAttribute("type", "String");
	meshElement->SetAttribute("value", "none");
    matElement->SetAttribute("type", "String");
	matElement->SetAttribute("value", "none");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newShieldElement->LinkEndChild(valueElement);
	newShieldElement->LinkEndChild(scriptElement);
	newShieldElement->LinkEndChild(meshElement);
	newShieldElement->LinkEndChild(matElement);
	newShieldElement->LinkEndChild(attrElement);

	xmlManager_->AddData("ShieldData", newShieldElement);

	ticpp::Element *newShieldLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newShieldLangElement->LinkEndChild(nameElement);
	newShieldLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("ShieldData", newShieldLangElement);
}

void DataManager::AddSoldier()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newsoldier%d", n);
	while(xmlManager_->GetData("SoilderData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newsoldier%d",n);
	}
	
	ticpp::Element *newSoldierElement = new ticpp::Element(newid);

	ticpp::Element * typeElement = new ticpp::Element("Type");
	ticpp::Element * valueElement = new ticpp::Element("Value");
	ticpp::Element * scriptElement = new ticpp::Element("Script");
	ticpp::Element * attrElement = new ticpp::Element("AttrModifer");
	ticpp::Element * attrTypeElement = new ticpp::Element("Type");
	ticpp::Element * attrAttackElement = new ticpp::Element("Attack");
	ticpp::Element * attrRangedElement = new ticpp::Element("RangedAttack");
	ticpp::Element * attrDefenceElement = new ticpp::Element("Defence");
	ticpp::Element * attrFormationElement = new ticpp::Element("Formation");
	ticpp::Element * attrInitiativeElement = new ticpp::Element("Initiative");
	ticpp::Element * attrActionElement = new ticpp::Element("ActionPoint");
	ticpp::Element * attrDetectionElement = new ticpp::Element("Detection");
	ticpp::Element * attrCovertElement = new ticpp::Element("Covert");
	ticpp::Element * attrInjuryElement = new ticpp::Element("Injury");
	ticpp::Element * attrConterElement = new ticpp::Element("Conter");
	ticpp::Element * injuryElement = new ticpp::Element("Injury");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");
	injuryElement->SetAttribute("type", "Int");
	injuryElement->SetAttribute("value", "0");

	attrTypeElement->SetAttribute("type", "Int");
	attrTypeElement->SetAttribute("value", "0");
	attrAttackElement->SetAttribute("type", "Float");
	attrAttackElement->SetAttribute("value", "0.0");
	attrRangedElement->SetAttribute("type", "Float");
	attrRangedElement->SetAttribute("value", "0.0");
	attrDefenceElement->SetAttribute("type", "Float");
	attrDefenceElement->SetAttribute("value", "0.0");
	attrFormationElement->SetAttribute("type", "Float");
	attrFormationElement->SetAttribute("value", "0.0");
	attrInitiativeElement->SetAttribute("type", "Float");
	attrInitiativeElement->SetAttribute("value", "0.0");
	attrActionElement->SetAttribute("type", "Float");
	attrActionElement->SetAttribute("value", "0.0");
	attrDetectionElement->SetAttribute("type", "Float");
	attrDetectionElement->SetAttribute("value", "0.0");
	attrCovertElement->SetAttribute("type", "Float");
	attrCovertElement->SetAttribute("value", "0.0");
	attrInjuryElement->SetAttribute("type", "Float");
	attrInjuryElement->SetAttribute("value", "0.0");
	attrConterElement->SetAttribute("type", "Float");
	attrConterElement->SetAttribute("value", "0.0");

	attrElement->LinkEndChild(attrTypeElement);
	attrElement->LinkEndChild(attrAttackElement);
	attrElement->LinkEndChild(attrRangedElement);
	attrElement->LinkEndChild(attrDefenceElement);
	attrElement->LinkEndChild(attrFormationElement);
	attrElement->LinkEndChild(attrInitiativeElement);
	attrElement->LinkEndChild(attrActionElement);
	attrElement->LinkEndChild(attrDetectionElement);
	attrElement->LinkEndChild(attrCovertElement);
	attrElement->LinkEndChild(attrInjuryElement);
	attrElement->LinkEndChild(attrConterElement);

	newSoldierElement->LinkEndChild(typeElement);
	newSoldierElement->LinkEndChild(valueElement);
	newSoldierElement->LinkEndChild(scriptElement);
	newSoldierElement->LinkEndChild(attrElement);
	newSoldierElement->LinkEndChild(injuryElement);

	xmlManager_->AddData("SoilderData", newSoldierElement);

	ticpp::Element *newSoldierLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newSoldierLangElement->LinkEndChild(nameElement);
	newSoldierLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("SoilderData", newSoldierLangElement);
}

void DataManager::AddSkill()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newskill%d", n);
	while(xmlManager_->GetData("SkillData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newskill%d",n);
	}
	
	ticpp::Element *newSkillElement = new ticpp::Element(newid);

	ticpp::Element *typeElement = new ticpp::Element("Type");
	ticpp::Element *maxRangeElement = new ticpp::Element("MaxRange");
	ticpp::Element *minRangeElement = new ticpp::Element("MinRange");
	ticpp::Element *areaElement = new ticpp::Element("Area");
	ticpp::Element *aptypeElement = new ticpp::Element("APType");
	ticpp::Element *apcostElement = new ticpp::Element("APCost");
	ticpp::Element *cooldownElement = new ticpp::Element("CoolDown");
	ticpp::Element *valueElement = new ticpp::Element("Value");
	ticpp::Element *iconElement = new ticpp::Element("Icon");
	ticpp::Element *scriptElement = new ticpp::Element("Script");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "2");
	maxRangeElement->SetAttribute("type", "Int");
	maxRangeElement->SetAttribute("value", "0");
	minRangeElement->SetAttribute("type", "Int");
	minRangeElement->SetAttribute("value", "0");
	areaElement->SetAttribute("type", "Int");
	areaElement->SetAttribute("value", "0");
	aptypeElement->SetAttribute("type", "Int");
	aptypeElement->SetAttribute("value", "0");
	apcostElement->SetAttribute("type", "float");
	apcostElement->SetAttribute("value", "0.0");
	cooldownElement->SetAttribute("type", "Int");
	cooldownElement->SetAttribute("value", "0");
	valueElement->SetAttribute("type", "Int");
	valueElement->SetAttribute("value", "0");
	iconElement->SetAttribute("type", "String");
	iconElement->SetAttribute("value", "none");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");

	newSkillElement->LinkEndChild(typeElement);
	newSkillElement->LinkEndChild(maxRangeElement);
	newSkillElement->LinkEndChild(minRangeElement);
	newSkillElement->LinkEndChild(areaElement);
	newSkillElement->LinkEndChild(aptypeElement);
	newSkillElement->LinkEndChild(apcostElement);
	newSkillElement->LinkEndChild(cooldownElement);
	newSkillElement->LinkEndChild(valueElement);
	newSkillElement->LinkEndChild(iconElement);
	newSkillElement->LinkEndChild(scriptElement);

	xmlManager_->AddData("SkillData", newSkillElement);

	ticpp::Element *newSkillLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newSkillLangElement->LinkEndChild(nameElement);
	newSkillLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("SkillData", newSkillLangElement);
}

void DataManager::AddEffect()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "neweffect%d", n);
	while(xmlManager_->GetData("EffectData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"neweffect%d",n);
	}
	
	ticpp::Element *newEffectElement = new ticpp::Element(newid);

	ticpp::Element *typeElement = new ticpp::Element("Type");
	ticpp::Element *iconElement = new ticpp::Element("Icon");
	ticpp::Element *scriptElement = new ticpp::Element("Script");

	typeElement->SetAttribute("type", "Int");
	typeElement->SetAttribute("value", "1");
	iconElement->SetAttribute("type", "String");
	iconElement->SetAttribute("value", "none");
	scriptElement->SetAttribute("type", "String");
	scriptElement->SetAttribute("value", "none");

	newEffectElement->LinkEndChild(typeElement);
	newEffectElement->LinkEndChild(iconElement);
	newEffectElement->LinkEndChild(scriptElement);

	xmlManager_->AddData("EffectData", newEffectElement);

	ticpp::Element *newEffectLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newEffectLangElement->LinkEndChild(nameElement);
	newEffectLangElement->LinkEndChild(describeElement);

	xmlManager_->AddLang("EffectData", newEffectLangElement);
}

void DataManager::AddString()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newstringkey%d",n);
	while(xmlManager_->GetStringTable(newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newstringkey%d",n);
	}

	ticpp::Element *newStringElement = new ticpp::Element(newid);
	newStringElement->SetAttribute("type", "String");
	newStringElement->SetAttribute("value", "String");
	xmlManager_->AddStringTable(newStringElement);
}

void DataManager::RemoveData(std::string _parent, std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	xmlManager_->RemoveData(_parent, tempid);
	xmlManager_->RemoveLang(_parent, tempid);
}

void DataManager::RemoveStrTable(std::wstring _key)
{
	std::string tempkey;
	UnicodeToUTF8(_key,tempkey);
	xmlManager_->RemoveStringTable(tempkey);
}

int DataManager::GetCount(std::string _parent)
{
	return xmlManager_->CountData(_parent);
}

int DataManager::GetStrTableCount()
{
	return xmlManager_->CountStringTable();
}

int DataManager::GetInt(std::string _parent, std::wstring _id, std::string _tag)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *rootElement = xmlManager_->GetData(_parent, tempid);
	if (rootElement == NULL) return 0;
	ticpp::Element *dataElement = rootElement->FirstChildElement(_tag, false);
	if (dataElement == NULL) return 0;
	int data = 0;
	dataElement->GetAttribute("value", &data, false);
	return data;
}

float DataManager::GetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *element = xmlManager_->GetData(_parent, tempid);
	if (element == NULL) return 0;
	ticpp::Element *attrElement = element->FirstChildElement("AttrModifer", false);
	if (attrElement == NULL) return 0;
	ticpp::Element *tempElement;
	float attr = 0;
	switch(_attrType)
	{
	case ATTR_ATTACK:
		tempElement = attrElement->FirstChildElement("Attack", false);
		break;
	case ATTR_RANGEDATTACK:
		tempElement = attrElement->FirstChildElement("RangedAttack", false);
		break;
	case ATTR_DEFENSE:
		tempElement = attrElement->FirstChildElement("Defence", false);
		break;
	case ATTR_FORMATION:
		tempElement = attrElement->FirstChildElement("Formation", false);
		break;
	case ATTR_INITIATIVE:
		tempElement = attrElement->FirstChildElement("Initiative", false);
		break;
	case ATTR_ACTIONPOINT:
		tempElement = attrElement->FirstChildElement("ActionPoint", false);
		break;
	case ATTR_DETECTION:
		tempElement = attrElement->FirstChildElement("Detection", false);
		break;
	case ATTR_COVERT:
		tempElement = attrElement->FirstChildElement("Covert", false);
		break;
	case ATTR_INJURY:
		tempElement = attrElement->FirstChildElement("Injury", false);
		break;
	case ATTR_COUNTER:
		tempElement = attrElement->FirstChildElement("Conter", false);
		break;
	default:
		return attr;
	}
	if (tempElement == NULL) return 0;
	tempElement->GetAttribute("value", &attr, false);
	return attr;
}

std::wstring DataManager::GetID(std::string _parent, int _index)
{
	return xmlManager_->GetDataID(_parent, _index);
}

std::wstring DataManager::GetStrTableID(int _index)
{
	return xmlManager_->GetStringTableID(_index);
}

std::wstring DataManager::GetLangStr(std::string _parent, std::wstring _id, std::string _tag)
{
	std::wstring emptyStr;
	UTF8ToUnicode("", emptyStr);
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *rootElement = xmlManager_->GetLang(_parent, tempid);
	if (rootElement == NULL) return emptyStr;
	ticpp::Element *dataElement = rootElement->FirstChildElement(_tag, false);
	if (dataElement == NULL) return emptyStr;
	std::string tempData;
	dataElement->GetAttribute("value", &tempData, false);
	std::wstring data;
	UTF8ToUnicode(tempData, data);
	return data;
}

std::wstring DataManager::GetDataStr(std::string _parent, std::wstring _id, std::string _tag)
{
	std::wstring emptyStr;
	UTF8ToUnicode("", emptyStr);
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *rootElement = xmlManager_->GetData(_parent, tempid);
	if (rootElement == NULL) return emptyStr;
	ticpp::Element *dataElement = rootElement->FirstChildElement(_tag, false);
	if (dataElement == NULL) return emptyStr;
	std::string tempData;
	dataElement->GetAttribute("value", &tempData, false);
	std::wstring data;
	UTF8ToUnicode(tempData, data);
	return data;
}

std::wstring DataManager::GetStrTable(std::wstring _key)
{
	std::wstring emptyStr;
	UTF8ToUnicode("", emptyStr);
	std::string tempkey;
	UnicodeToUTF8(_key, tempkey);
	ticpp::Element *stringElement = xmlManager_->GetStringTable(tempkey);
	if (stringElement == NULL) return emptyStr;
	std::string tempString;
	tempString = stringElement->GetAttribute("value");
	std::wstring stringValue;
	UTF8ToUnicode(tempString, stringValue);
	return stringValue;
}

bool DataManager::SetInt(std::string _parent, std::wstring _id, std::string _tag, int _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return xmlManager_->SetDataInt(_parent, tempid, _tag, _value);
}

bool DataManager::SetAttribute(std::string _parent, std::wstring _id, BasicAttr _attrType, float _attr)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	switch(_attrType)
	{
	case ATTR_ATTACK:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Attack", _attr);
	case ATTR_RANGEDATTACK:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "RangedAttack", _attr);
	case ATTR_DEFENSE:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Defence", _attr);
	case ATTR_FORMATION:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Formation", _attr);
	case ATTR_INITIATIVE:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Initiative", _attr);
	case ATTR_ACTIONPOINT:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "ActionPoint", _attr);
	case ATTR_DETECTION:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Detection", _attr);
	case ATTR_COVERT:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Covert", _attr);
	case ATTR_INJURY:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Injury", _attr);
	case ATTR_COUNTER:
		return xmlManager_->SetDataAttr(_parent, tempid, "AttrModifer", "Conter", _attr);
	default:
		return false;
	}
}

bool DataManager::SetID(std::string _parent, std::wstring _oldID, std::wstring _newID)
{
	std::string tempoldid;
	UnicodeToUTF8(_oldID,tempoldid);
	std::string tempid;
	UnicodeToUTF8(_newID,tempid);
	ticpp::Element *element = xmlManager_->GetData(_parent, tempoldid);
	if (element == NULL) return false;
	element = xmlManager_->GetData(_parent, tempid);
	if (element == NULL)
	{
		xmlManager_->SetDataID(_parent, tempoldid, tempid);
		xmlManager_->SetLangID(_parent, tempoldid, tempid);
		return true;
	}
	return false;
}

bool DataManager::SetStrTableID(std::wstring _oldKey, std::wstring _newKey)
{
	std::string tempoldkey;
	UnicodeToUTF8(_oldKey,tempoldkey);
	std::string tempnewkey;
	UnicodeToUTF8(_newKey,tempnewkey);
	ticpp::Element *element = xmlManager_->GetStringTable(tempoldkey);
	if (element == NULL) return false;
	element = xmlManager_->GetStringTable(tempnewkey);
	if (element == NULL)
	{
		xmlManager_->SetStringTableID(tempoldkey, tempnewkey);
		return true;
	}
	return false;
}

bool DataManager::SetLangStr(std::string _parent, std::wstring _id, std::string _tag, std::wstring _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempvalue;
	UnicodeToUTF8(_value, tempvalue);
	return xmlManager_->SetLang(_parent, tempid, _tag, tempvalue);
}

bool DataManager::SetDataStr(std::string _parent, std::wstring _id, std::string _tag, std::wstring _value)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	std::string tempvalue;
	UnicodeToUTF8(_value,tempvalue);
	return xmlManager_->SetDataStr(_parent, tempid, _tag, tempvalue);
}

bool DataManager::SetStrTable(std::wstring _key, std::wstring _value)
{
	std::string tempkey;
	UnicodeToUTF8(_key, tempkey);
	std::string tempvalue;
	UnicodeToUTF8(_value, tempvalue);
	return xmlManager_->SetStringTable(tempkey, tempvalue);
}