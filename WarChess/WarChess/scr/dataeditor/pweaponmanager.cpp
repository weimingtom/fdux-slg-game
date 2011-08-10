#include "pweaponmanager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

PWeaponManager::PWeaponManager()
{

}

PWeaponManager::~PWeaponManager()
{

}

bool PWeaponManager::LoadMod(std::wstring modName, std::wstring langName, bool editorMode)
{
	mModPath = L".\\..\\Mod\\" + modName + L"\\";

	std::wstring tempPath;
	tempPath = mModPath + L"data\\primaryweapon.xml";

	UnicodeToANSI(tempPath, mDataPath);

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));

	hFind = FindFirstFile(tempPath.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		mDataFile.LoadFile(mDataPath.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	else if(!editorMode)
	{
		mModPath = L".\\..\\Mod\\common\\";
		tempPath = mModPath + L"data\\primaryweapon.xml";
		UnicodeToANSI(tempPath, mDataPath);
		hFind = FindFirstFile(tempPath.c_str(),&findFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			mDataFile.LoadFile(mDataPath.c_str(),TIXML_ENCODING_UTF8);
			FindClose(hFind);
		}
		else
		{
			CreateDataFile();
		}
	}
	else
	{
		CreateDataFile();
	}

	LoadLang(langName);

	return true;
}

bool PWeaponManager::LoadLang(std::wstring langName)
{
	std::wstring tempPath;
	tempPath = mModPath + L"Lang\\" + langName + L"\\primaryweapon.xml";

	UnicodeToANSI(tempPath, mLangPath);

	WIN32_FIND_DATA findFileData;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	memset(&findFileData,0,sizeof(findFileData));

	hFind = FindFirstFile(tempPath.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		mLangFile.LoadFile(mLangPath.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	else
	{
		CreateLangFile();
	}
	return true;
}

bool PWeaponManager::CreateDataFile()
{
	mDataFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "PrimaryWeapon" );
	mDataFile.LinkEndChild(decl);
	mDataFile.LinkEndChild(element);
	return true;
}

bool PWeaponManager::CreateLangFile()
{
	mLangFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "PrimaryWeapon" );
	mLangFile.LinkEndChild(decl);
	mLangFile.LinkEndChild(element);
	return true;
}

bool PWeaponManager::SaveData()
{
	if(mDataPath.size()> 0)
	{
		ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
		if(element)
		{
			if(!element->NoChildren())
				mDataFile.SaveFile(mDataPath.c_str());
			else
				DeleteFileA(mDataPath.c_str());
		}

	}
	return true;
}

bool PWeaponManager::SaveLang()
{
	if(mLangPath.size() > 0)
	{
		ticpp::Element *element = mLangFile.FirstChildElement("PrimaryWeapon");
		if(element)
		{
			if(!element->NoChildren())
				mLangFile.SaveFile(mLangPath.c_str());
			else
				DeleteFileA(mLangPath.c_str());
		}
	}
	return true;
}

int PWeaponManager::GetNum()
{
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	if(element)
	{
		if(element->NoChildren())
			return 0;
		else
		{
			int num = 0;
			ticpp::Iterator<ticpp::Element> child;
			for(child = child.begin(element); child != child.end(); child++)
				num++;
			return num;
		}
	}
	return 0;
}

void PWeaponManager::AddPWeapon()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newprimaryweapon%d",n);
	ticpp::Element *rootelement = mDataFile.FirstChildElement("PrimaryWeapon");
	while(rootelement->FirstChildElement(newid,false))
	{
		n = n + 1;
		sprintf_s(newid,20,"newprimaryweapon%d",n);
	}
	ticpp::Element *element = new ticpp::Element(newid);
	element->SetAttribute("Attack",0);
	element->SetAttribute("Defence",0);
	element->SetAttribute("Formation",0);
	element->SetAttribute("Initiative",0);
	element->SetAttribute("ActionPoint",0);
	element->SetAttribute("Covert",0);
	element->SetAttribute("Script","");
	element->SetAttribute("PWeaponType",PWEAPON_NONE);
	element->SetAttribute("ModuleName","");
	element->SetAttribute("IdleAnimName","");
	element->SetAttribute("ActAnimName","");
	element->SetAttribute("Value",0);

	rootelement->LinkEndChild(element);

	ticpp::Element *langrootelement = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *langelement = langrootelement->FirstChildElement(newid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(newid);
		langelement->SetAttribute("Name",newid);
		langelement->SetText("Please add a description.");
		langrootelement->LinkEndChild(langelement);
	}
}

void PWeaponManager::DelPWeapon(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *dataelement = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Node *datachildelement = dataelement->FirstChildElement(tempid,false);
	if(datachildelement)
	{
		dataelement->RemoveChild(datachildelement);
	}
	ticpp::Element *langelement = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Node *langchildelement = langelement->FirstChildElement(tempid,false);
	if(langchildelement)
	{
		langelement->RemoveChild(langchildelement);
	}
}

std::wstring PWeaponManager::GetID(int index)
{
	int n = 0;
	std::string id;
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Iterator<ticpp::Element> child;
	child = child.begin(element);
	while(n < index  )
	{
		child++;
		n++;
	}
	child->GetValue(&id);
	std::wstring tempid;
	UTF8ToUnicode(id,tempid);
	return tempid;
}

std::wstring PWeaponManager::GetName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);
		langelement->SetAttribute("Name",tempid);
		langelement->SetText("Please add a description.");
		element->LinkEndChild(langelement);
	}
	std::string name;
	name = langelement->GetAttribute("Name");
	std::wstring tempname;
	UTF8ToUnicode(name,tempname);
	return tempname;
}

std::wstring PWeaponManager::GetDescription(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);
		langelement->SetAttribute("Name",tempid);
		langelement->SetText("Please add a description.");
		element->LinkEndChild(langelement);
	}
	std::string description;
	description = langelement->GetText();
	std::wstring tempdescription;
	UTF8ToUnicode(description,tempdescription);
	return tempdescription;
}

std::wstring PWeaponManager::GetScriptName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	std::string script;
	script = dataelement->GetAttribute("Script");
	std::wstring tempscript;
	UTF8ToUnicode(script,tempscript);
	return tempscript;
}

int PWeaponManager::GetAttr(std::wstring id, BasicAttr attrType)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	int attr = 0;
	switch(attrType)
	{
	case ATTR_ATTACK:
		dataelement->GetAttribute("Attack",&attr);
		break;
	case ATTR_DEFENSE:
		dataelement->GetAttribute("Defence",&attr);
		break;
	case ATTR_FORMATION:
		dataelement->GetAttribute("Formation",&attr);
		break;
	case ATTR_INITIATIVE:
		dataelement->GetAttribute("Initiative",&attr);
		break;
	case ATTR_ACTIONPOINT:
		dataelement->GetAttribute("ActionPoint",&attr);
		break;
	case ATTR_COVERT:
		dataelement->GetAttribute("Covert",&attr);
		break;
	default:
		return attr;
	}
	return attr;
}

int PWeaponManager::GetPWeaponType(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	int pwtypeint = 0;
	dataelement->GetAttribute("PWeaponType",&pwtypeint);
	return pwtypeint;
}

std::wstring PWeaponManager::GetModuleName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	std::string script;
	script = dataelement->GetAttribute("ModuleName");
	std::wstring tempmodulename;
	UTF8ToUnicode(script,tempmodulename);
	return tempmodulename;
}

std::wstring PWeaponManager::GetIdleAnimName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	std::string script;
	script = dataelement->GetAttribute("IdleAnimName");
	std::wstring tempanimname;
	UTF8ToUnicode(script,tempanimname);
	return tempanimname;
}

std::wstring PWeaponManager::GetActAnimName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	std::string script;
	script = dataelement->GetAttribute("ActAnimName");
	std::wstring tempanimname;
	UTF8ToUnicode(script,tempanimname);
	return tempanimname;
}

int PWeaponManager::GetValue(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	int ivalue = 0;
	dataelement->GetAttribute("Value",&ivalue);
	return ivalue;
}

bool PWeaponManager::SetID(std::wstring oldid, std::wstring id)
{
	std::string tempoldid;
	UnicodeToUTF8(oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	//ÅÐ¶ÏÊÇ·ñ´æÔÚÖØ¸´id
	if(element->FirstChildElement(tempid,false) == NULL)
	{
		ticpp::Element *dataelement = element->FirstChildElement(tempoldid);
		dataelement->SetValue(tempid);
		ticpp::Element *langelement = mLangFile.FirstChildElement("PrimaryWeapon");
		ticpp::Element *langchildelement = langelement->FirstChildElement(tempoldid,false);
		if(langchildelement == NULL)
		{
			langchildelement = new ticpp::Element(tempid);
			langchildelement->SetAttribute("Name",tempid);
			langchildelement->SetText("Please add a description.");
			langelement->LinkEndChild(langchildelement);
		}
		else
			langchildelement->SetValue(tempid);
		return true;
	}
	return false;
}

bool PWeaponManager::SetName(std::wstring id, std::wstring name)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempname;
	UnicodeToUTF8(name,tempname);
	ticpp::Element *element = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *langelement = element->FirstChildElement(tempid);
	langelement->SetAttribute("Name",tempname);
	return true;
}

bool PWeaponManager::SetDescription(std::wstring id, std::wstring descripition)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempdescripition;
	UnicodeToUTF8(descripition,tempdescripition);
	ticpp::Element *element = mLangFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *langelement = element->FirstChildElement(tempid);
	langelement->SetText(tempdescripition);
	return true;
}

bool PWeaponManager::SetScriptName(std::wstring id, std::wstring script)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempscript;
	UnicodeToUTF8(script,tempscript);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("Script",tempscript);
	return true;
}

bool PWeaponManager::SetAttr(std::wstring id, BasicAttr attrType, int attr)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	switch(attrType)
	{
	case ATTR_ATTACK:
		dataelement->SetAttribute("Attack",attr);
		break;
	case ATTR_DEFENSE:
		dataelement->SetAttribute("Defence",attr);
		break;
	case ATTR_FORMATION:
		dataelement->SetAttribute("Formation",attr);
		break;
	case ATTR_INITIATIVE:
		dataelement->SetAttribute("Initiative",attr);
		break;
	case ATTR_ACTIONPOINT:
		dataelement->SetAttribute("ActionPoint",attr);
		break;
	case ATTR_COVERT:
		dataelement->SetAttribute("Covert",attr);
		break;
	default:
		return false;
	}
	return true;
}

bool PWeaponManager::SetModuleName(std::wstring id, std::wstring modulename)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempmodulename;
	UnicodeToUTF8(modulename,tempmodulename);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("ModuleName",tempmodulename);
	return true;
}

bool PWeaponManager::SetIdleAnimName(std::wstring id, std::wstring animname)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempanimname;
	UnicodeToUTF8(animname,tempanimname);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("IdleAnimName",tempanimname);
	return true;
}

bool PWeaponManager::SetActAnimName(std::wstring id, std::wstring animname)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempanimname;
	UnicodeToUTF8(animname,tempanimname);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("ActAnimName",tempanimname);
	return true;
}

bool PWeaponManager::SetPWeaponType(std::wstring id, int type)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("PWeaponType",type);
	return true;
}

bool PWeaponManager::SetValue(std::wstring id, int ivalue)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("PrimaryWeapon");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("Value",ivalue);
	return true;
}