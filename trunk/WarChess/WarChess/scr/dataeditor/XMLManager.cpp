#include "XMLManager.h"
#include "conversion.h"
#include <Windows.h>

bool XMLManager::LoadMod(std::wstring _modName,std::wstring _langName, bool _editorMode)
{
	std::wstring tempPath = L".\\..\\Mod\\" + _modName + L"\\data\\datafile.xml";
	UnicodeToANSI(tempPath, dataPath_);

	WIN32_FIND_DATA findFileData;
	memset(&findFileData,0,sizeof(findFileData));

	HANDLE hFind = FindFirstFile(tempPath.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		dataFile_.LoadFile(dataPath_.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	else if(!_editorMode)
	{
		tempPath = L".\\..\\Mod\\common\\data\\datafile.xml";
		UnicodeToANSI(tempPath, dataPath_);
		hFind = FindFirstFile(tempPath.c_str(),&findFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			dataFile_.LoadFile(dataPath_.c_str(),TIXML_ENCODING_UTF8);
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

	LoadLang(_modName, _langName, _editorMode);

	return true;
}

bool XMLManager::LoadLang(std::wstring _modName, std::wstring _langName, bool _editorMode)
{
	std::wstring tempPath = L".\\..\\Mod\\" + _modName + L"\\Lang\\" + _langName + L"\\datafile.xml";
	UnicodeToANSI(tempPath, langPath_);

	WIN32_FIND_DATA findFileData;
	memset(&findFileData,0,sizeof(findFileData));

	HANDLE hFind = FindFirstFile(tempPath.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		langFile_.LoadFile(langPath_.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	else if(!_editorMode)
	{
		tempPath = L".\\..\\Mod\\common\\Lang\\chinese\\datafile.xml";
		UnicodeToANSI(tempPath, langPath_);
		hFind = FindFirstFile(tempPath.c_str(),&findFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			langFile_.LoadFile(langPath_.c_str(),TIXML_ENCODING_UTF8);
			FindClose(hFind);
		}
		else
		{
			CreateLangFile();
		}
	}
	else
	{
		CreateLangFile();
	}

	LoadStringTable(_modName, _langName, _editorMode);

	return true;
}

bool XMLManager::LoadStringTable(std::wstring _modName, std::wstring _langName, bool _editorMode)
{
	std::wstring tempPath = L".\\..\\Mod\\" + _modName + L"\\Lang\\" + _langName + L"\\stringtable.xml";
	UnicodeToANSI(tempPath, stringTablePath_);

	WIN32_FIND_DATA findFileData;
	memset(&findFileData,0,sizeof(findFileData));

	HANDLE hFind = FindFirstFile(tempPath.c_str(),&findFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		stringTableFile_.LoadFile(stringTablePath_.c_str(),TIXML_ENCODING_UTF8);
		FindClose(hFind);
	}
	else if(!_editorMode)
	{
		tempPath = L".\\..\\Mod\\common\\Lang\\chinese\\stringtable.xml";
		UnicodeToANSI(tempPath, stringTablePath_);
		hFind = FindFirstFile(tempPath.c_str(),&findFileData);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			stringTableFile_.LoadFile(stringTablePath_.c_str(),TIXML_ENCODING_UTF8);
			FindClose(hFind);
		}
		else
		{
			CreateStringTableFile();
		}
	}
	else
	{
		CreateStringTableFile();
	}

	return true;
}

bool XMLManager::SaveData()
{
	try
	{
		if (dataPath_.size() > 0) dataFile_.SaveFile(dataPath_);
	}
	catch (ticpp::Exception &err)
	{
		std::cout<<err.what();
	}
	return true;
}

bool XMLManager::SaveLang()
{
	try
	{
		if (langPath_.size() > 0) langFile_.SaveFile(langPath_);
	}
	catch (ticpp::Exception &err)
	{
		std::cout<<err.what();
	}
	return true;
}

bool XMLManager::SaveStringTable()
{
	try
	{
		if (stringTablePath_.size() > 0) stringTableFile_.SaveFile(stringTablePath_);
	}
	catch (ticpp::Exception &err)
	{
		std::cout<<err.what();
	}
	return true;
}

bool XMLManager::AddData(std::string _parent, ticpp::Element *_element)
{
	ticpp::Element *parentElement = dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);
	if (parentElement != NULL)
	{
		parentElement->LinkEndChild(_element);
		return true;
	}
	return false;
}

bool XMLManager::AddLang(std::string _parent, ticpp::Element *_element)
{
	ticpp::Element *parentElement = langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);
	if (parentElement != NULL)
	{
		parentElement->LinkEndChild(_element);
		return true;
	}
	return false;
}

bool XMLManager::AddStringTable(ticpp::Element *_element)
{
	ticpp::Element *parentElement = stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false);
	if (parentElement != NULL)
	{
		parentElement->LinkEndChild(_element);
		return true;
	}
	return false;
}

bool XMLManager::RemoveData(std::string _parent, std::string _child)
{
	ticpp::Element *parentElement = dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);
	ticpp::Element *childElement = parentElement->FirstChildElement(_child, false);
	if(childElement != NULL)
	{
		parentElement->RemoveChild(childElement);
		return true;
	}
	return false;
}

bool XMLManager::RemoveLang(std::string _parent, std::string _child)
{
	ticpp::Element *parentElement = langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);
	ticpp::Element *childElement = parentElement->FirstChildElement(_child, false);
	if(childElement != NULL)
	{
		parentElement->RemoveChild(childElement);
		return true;
	}
	return false;
}

bool XMLManager::RemoveStringTable(std::string _key)
{
	ticpp::Element *parentElement = stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false);
	ticpp::Element *childElement = parentElement->FirstChildElement(_key, false);
	if(childElement != NULL)
	{
		parentElement->RemoveChild(childElement);
		return true;
	}
	return false;
}

ticpp::Element* XMLManager::GetData(std::string _parent, std::string _child)
{
	return dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)->FirstChildElement(_child, false);
}

ticpp::Element* XMLManager::GetLang(std::string _parent, std::string _child)
{
	return langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)->FirstChildElement(_child, false);
}

ticpp::Element* XMLManager::GetStringTable(std::string _key)
{
	return stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false)->FirstChildElement(_key, false);
}

std::wstring XMLManager::GetDataID(std::string _parent, int _index)
{	
	ticpp::Element *parentElement = dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);
	ticpp::Iterator<ticpp::Element> child;
	child = child.begin(parentElement);
	int n = 0;
	while(n < _index)
	{
		child++;
		n++;
	}
	std::string tempid;
	child->GetValue(&tempid);
	std::wstring id;
	UTF8ToUnicode(tempid,id);
	return id;
}

std::wstring XMLManager::GetLangID(std::string _parent, int _index)
{
	return GetDataID(_parent, _index);
}

std::wstring XMLManager::GetStringTableID(int _index)
{
	ticpp::Element *parentElement = stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false);
	ticpp::Iterator<ticpp::Element> child;
	child = child.begin(parentElement);
	int n = 0;
	while(n < _index)
	{
		child++;
		n++;
	}
	std::string tempid;
	child->GetValue(&tempid);
	std::wstring id;
	UTF8ToUnicode(tempid,id);
	return id;
}

bool XMLManager::SetDataStr(std::string _parent, std::string _child, std::string _tag, std::string _value)
{
	dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->FirstChildElement(_tag, false)
		->SetAttribute("value", _value);
	return true;
}

bool XMLManager::SetDataInt(std::string _parent, std::string _child, std::string _tag, int _value)
{
	dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->FirstChildElement(_tag, false)
		->SetAttribute("value", _value);
	return true;
}

bool XMLManager::SetDataAttr(std::string _parent, std::string _child, std::string _tag, std::string _attr, int _value)
{
	dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->FirstChildElement(_tag, false)
		->FirstChildElement(_attr, false)
		->SetAttribute("value", _value);
	return true;
}

bool XMLManager::SetLang(std::string _parent, std::string _child, std::string _tag, std::string _value)
{
	langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->FirstChildElement(_tag, false)
		->SetAttribute("value", _value);
	return true;
}

bool XMLManager::SetStringTable(std::string _key, std::string _value)
{
	stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false)
		->FirstChildElement(_key, false)
		->SetAttribute("value", _value);
	return true;
}

bool XMLManager::SetDataID(std::string _parent, std::string _child, std::string _id)
{
	dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->SetValue(_id);
	return true;
}

bool XMLManager::SetLangID(std::string _parent, std::string _child, std::string _id)
{
	langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false)
		->FirstChildElement(_child, false)
		->SetValue(_id);
	return true;
}

bool XMLManager::SetStringTableID(std::string _key, std::string _id)
{
	stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false)
		->FirstChildElement(_key, false)
		->SetValue(_id);
	return true;
}

int XMLManager::CountData(std::string _parent)
{
	int count = 0;
	ticpp::Element * parentElement = dataFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);	
	if(parentElement != NULL)
	{
		if(!parentElement->NoChildren())
		{
			ticpp::Iterator<ticpp::Element> child;
			for(child = child.begin(parentElement); child != child.end(); child++) count++;
		}
	}
	return count;
}

int XMLManager::CountLang(std::string _parent)
{
	int count = 0;
	ticpp::Element * parentElement = langFile_.FirstChildElement("StaticData", false)->FirstChildElement(_parent, false);	
	if(parentElement != NULL)
	{
		if(!parentElement->NoChildren())
		{
			ticpp::Iterator<ticpp::Element> child;
			for(child = child.begin(parentElement); child != child.end(); child++) count++;
		}
	}
	return count;
}

int XMLManager::CountStringTable()
{
	int count = 0;
	ticpp::Element * parentElement = stringTableFile_.FirstChildElement("StaticData", false)->FirstChildElement("StringTable", false);	
	if(parentElement != NULL)
	{
		if(!parentElement->NoChildren())
		{
			ticpp::Iterator<ticpp::Element> child;
			for(child = child.begin(parentElement); child != child.end(); child++) count++;
		}
	}
	return count;
}

bool XMLManager::CreateDataFile()
{
	dataFile_.Clear();

	ticpp::Declaration * dataDeclaration = new ticpp::Declaration("1.0", "utf-8", "");
	ticpp::Element * staticDataElement = new ticpp::Element("StaticData");
	ticpp::Element * soldierDataElement = new ticpp::Element("SoilderData");
	ticpp::Element * horseDataElement = new ticpp::Element("HorseData");	
	ticpp::Element * pweaponDataElement = new ticpp::Element("PweaponData");
	ticpp::Element * sweaponDataElement = new ticpp::Element("SweaponData");
	ticpp::Element * shieldDataElement = new ticpp::Element("ShieldData");
	ticpp::Element * armorDataElement = new ticpp::Element("ArmorData");
	
	staticDataElement->LinkEndChild(soldierDataElement);
	staticDataElement->LinkEndChild(horseDataElement);
	staticDataElement->LinkEndChild(pweaponDataElement);
	staticDataElement->LinkEndChild(sweaponDataElement);
	staticDataElement->LinkEndChild(shieldDataElement);
	staticDataElement->LinkEndChild(armorDataElement);

	dataFile_.LinkEndChild(dataDeclaration);
	dataFile_.LinkEndChild(staticDataElement);

	return true;
}

bool XMLManager::CreateLangFile()
{
	langFile_.Clear();

	ticpp::Declaration * dataDeclaration = new ticpp::Declaration("1.0", "utf-8", "");
	ticpp::Element * staticDataElement = new ticpp::Element("StaticData");
	ticpp::Element * soldierDataElement = new ticpp::Element("SoilderData");
	ticpp::Element * horseDataElement = new ticpp::Element("HorseData");	
	ticpp::Element * pweaponDataElement = new ticpp::Element("PweaponData");
	ticpp::Element * sweaponDataElement = new ticpp::Element("SweaponData");
	ticpp::Element * shieldDataElement = new ticpp::Element("ShieldData");
	ticpp::Element * armorDataElement = new ticpp::Element("ArmorData");
	
	staticDataElement->LinkEndChild(soldierDataElement);
	staticDataElement->LinkEndChild(horseDataElement);
	staticDataElement->LinkEndChild(pweaponDataElement);
	staticDataElement->LinkEndChild(sweaponDataElement);
	staticDataElement->LinkEndChild(shieldDataElement);
	staticDataElement->LinkEndChild(armorDataElement);

	langFile_.LinkEndChild(dataDeclaration);
	langFile_.LinkEndChild(staticDataElement);

	return true;
}

bool XMLManager::CreateStringTableFile()
{
	stringTableFile_.Clear();

	ticpp::Declaration * dataDeclaration = new ticpp::Declaration("1.0", "utf-8", "");
	ticpp::Element * staticDataElement = new ticpp::Element("StaticData");
	ticpp::Element * stringTableElement = new ticpp::Element("StringTable");
	
	staticDataElement->LinkEndChild(stringTableElement);

	stringTableFile_.LinkEndChild(dataDeclaration);
	stringTableFile_.LinkEndChild(staticDataElement);

	return true;
}