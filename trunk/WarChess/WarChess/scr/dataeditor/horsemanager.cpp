#include "horsemanager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

HorseManager::HorseManager()
{

}

HorseManager::~HorseManager()
{

}

bool HorseManager::LoadMod(std::wstring modName, std::wstring langName, bool editorMode)
{
	mModPath = L".\\..\\Mod\\" + modName + L"\\";

	std::wstring tempPath;
	tempPath = mModPath + L"data\\horse.xml";

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
		tempPath = mModPath + L"data\\horse.xml";
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

bool HorseManager::LoadLang(std::wstring langName)
{
	std::wstring tempPath;
	tempPath = mModPath + L"Lang\\" + langName + L"\\horse.xml";

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

bool HorseManager::CreateDataFile()
{
	mDataFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "Horse" );
	mDataFile.LinkEndChild(decl);
	mDataFile.LinkEndChild(element);
	return true;
}

bool HorseManager::CreateLangFile()
{
	mLangFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "Horse" );
	mLangFile.LinkEndChild(decl);
	mLangFile.LinkEndChild(element);
	return true;
}

bool HorseManager::SaveData()
{
	if(mDataPath.size()> 0)
	{
		ticpp::Element *element = mDataFile.FirstChildElement("Horse");
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

bool HorseManager::SaveLang()
{
	if(mLangPath.size() > 0)
	{
		ticpp::Element *element = mLangFile.FirstChildElement("Horse");
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

int HorseManager::GetNum()
{
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
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

void HorseManager::AddHorse()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newhorse%d",n);
	ticpp::Element *rootelement = mDataFile.FirstChildElement("Horse");
	while(rootelement->FirstChildElement(newid,false))
	{
		n = n + 1;
		sprintf_s(newid,20,"newhorse%d",n);
	}
	ticpp::Element *element = new ticpp::Element(newid);
	element->SetAttribute("Attack",0);
	element->SetAttribute("RangedAttack",0);
	element->SetAttribute("Defence",0);
	element->SetAttribute("Formation",0);
	element->SetAttribute("Initiative",0);
	element->SetAttribute("ActionPoint",0);
	element->SetAttribute("Detection",0);
	element->SetAttribute("Covert",0);
	element->SetAttribute("Script","");
	element->SetAttribute("Value",0);

	rootelement->LinkEndChild(element);

	ticpp::Element *langrootelement = mLangFile.FirstChildElement("Horse");
	ticpp::Element *langelement = langrootelement->FirstChildElement(newid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(newid);
		langelement->SetAttribute("Name",newid);
		langelement->SetText("Please add a description.");
		langrootelement->LinkEndChild(langelement);
	}
}

void HorseManager::DelHorse(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *dataelement = mDataFile.FirstChildElement("Horse");
	ticpp::Node *datachildelement = dataelement->FirstChildElement(tempid,false);
	if(datachildelement)
	{
		dataelement->RemoveChild(datachildelement);
	}
	ticpp::Element *langelement = mLangFile.FirstChildElement("Horse");
	ticpp::Node *langchildelement = langelement->FirstChildElement(tempid,false);
	if(langchildelement)
	{
		langelement->RemoveChild(langchildelement);
	}
}

std::wstring HorseManager::GetID(int index)
{
	int n = 0;
	std::string id;
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
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

std::wstring HorseManager::GetName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("Horse");
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

std::wstring HorseManager::GetDescription(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("Horse");
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

std::wstring HorseManager::GetScriptName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	std::string script;
	script = dataelement->GetAttribute("Script");
	std::wstring tempscript;
	UTF8ToUnicode(script,tempscript);
	return tempscript;
}

int HorseManager::GetAttr(std::wstring id, BasicAttr attrType)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	int attr = 0;
	switch(attrType)
	{
	case ATTR_ATTACK:
		dataelement->GetAttribute("Attack",&attr);
		break;
	case ATTR_RANGEDATTACK:
		dataelement->GetAttribute("RangedAttack",&attr);
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
	case ATTR_DETECTION:
		dataelement->GetAttribute("Detection",&attr);
		break;
	case ATTR_COVERT:
		dataelement->GetAttribute("Covert",&attr);
		break;
	default:
		return attr;
	}
	return attr;
}

int HorseManager::GetValue(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	int ivalue = 0;
	dataelement->GetAttribute("Value",&ivalue);
	return ivalue;
}

bool HorseManager::SetID(std::wstring oldid, std::wstring id)
{
	std::string tempoldid;
	UnicodeToUTF8(oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	//ÅÐ¶ÏÊÇ·ñ´æÔÚÖØ¸´id
	if(element->FirstChildElement(tempid,false) == NULL)
	{
		ticpp::Element *dataelement = element->FirstChildElement(tempoldid);
		dataelement->SetValue(tempid);
		ticpp::Element *langelement = mLangFile.FirstChildElement("Horse");
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

bool HorseManager::SetName(std::wstring id, std::wstring name)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempname;
	UnicodeToUTF8(name,tempname);
	ticpp::Element *element = mLangFile.FirstChildElement("Horse");
	ticpp::Element *langelement = element->FirstChildElement(tempid);
	langelement->SetAttribute("Name",tempname);
	return true;
}

bool HorseManager::SetDescription(std::wstring id, std::wstring descripition)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempdescripition;
	UnicodeToUTF8(descripition,tempdescripition);
	ticpp::Element *element = mLangFile.FirstChildElement("Horse");
	ticpp::Element *langelement = element->FirstChildElement(tempid);
	langelement->SetText(tempdescripition);
	return true;
}

bool HorseManager::SetScriptName(std::wstring id, std::wstring script)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempscript;
	UnicodeToUTF8(script,tempscript);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("Script",tempscript);
	return true;
}

bool HorseManager::SetAttr(std::wstring id, BasicAttr attrType, int attr)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	switch(attrType)
	{
	case ATTR_ATTACK:
		dataelement->SetAttribute("Attack",attr);
		break;
	case ATTR_RANGEDATTACK:
		dataelement->SetAttribute("RangedAttack",attr);
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
	case ATTR_DETECTION:
		dataelement->SetAttribute("Detection",attr);
		break;
	case ATTR_COVERT:
		dataelement->SetAttribute("Covert",attr);
		break;
	default:
		return false;
	}
	return true;
}

bool HorseManager::SetValue(std::wstring id, int ivalue)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("Horse");
	ticpp::Element *dataelement = element->FirstChildElement(tempid);
	dataelement->SetAttribute("Value",ivalue);
	return true;
}