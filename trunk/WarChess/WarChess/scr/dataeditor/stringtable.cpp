#include "stringtable.h"

#include "conversion.h"
#include <Windows.h>

StringTable::StringTable()
{

}

StringTable::~StringTable()
{

}

bool StringTable::LoadLang(std::wstring langName, bool editorMode)
{
	std::wstring tempPath;
	tempPath = L".\\..\\Mod\\common\\Lang\\" + langName + L"\\string.xml";

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
	else if(!editorMode)
	{
		tempPath = L".\\..\\Mod\\common\\Lang\\chinese\\string.xml";
		UnicodeToANSI(tempPath, mLangPath);
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
	}
	else
	{
		CreateLangFile();
	}
	return true;
}

bool StringTable::CreateLangFile()
{
	mLangFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "StringTable" );
	mLangFile.LinkEndChild(decl);
	mLangFile.LinkEndChild(element);
	return true;
}


bool StringTable::SaveLang()
{
	if(mLangPath.size() > 0)
	{
		ticpp::Element *element = mLangFile.FirstChildElement("StringTable");
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

void StringTable::AddString()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newstringkey%d",n);


	ticpp::Element *langrootelement = mLangFile.FirstChildElement("StringTable");
	ticpp::Element *langelement = langrootelement->FirstChildElement(newid,false);
	while(langelement)
	{
		n = n + 1;
		sprintf_s(newid,20,"newstringkey%d",n);
		langelement = langrootelement->FirstChildElement(newid,false);
	}
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(newid);
		langelement->SetAttribute("type", "String");
		langelement->SetAttribute("value", "String");
		langrootelement->LinkEndChild(langelement);
	}
}

void StringTable::DelString(std::wstring key)
{
	std::string tempkey;
	UnicodeToUTF8(key,tempkey);
	ticpp::Element *langelement = mLangFile.FirstChildElement("StringTable");
	ticpp::Node *langchildelement = langelement->FirstChildElement(tempkey,false);
	if(langchildelement)
	{
		langelement->RemoveChild(langchildelement);
	}
}

int StringTable::GetNum()
{
	ticpp::Element *element = mLangFile.FirstChildElement("StringTable");
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

std::wstring StringTable::GetKey(int index)
{
	int n = 0;
	std::string key;
	ticpp::Element *element = mLangFile.FirstChildElement("StringTable");
	ticpp::Iterator<ticpp::Element> child;
	child = child.begin(element);
	while(n < index  )
	{
		child++;
		n++;
	}
	child->GetValue(&key);
	std::wstring tempkey;
	UTF8ToUnicode(key,tempkey);
	return tempkey;
}

bool StringTable::SetKey(std::wstring key, std::wstring newkey)
{
	std::string tempkey;
	UnicodeToUTF8(key,tempkey);
	std::string tempnewkey;
	UnicodeToUTF8(newkey,tempnewkey);
	ticpp::Element *element = mLangFile.FirstChildElement("StringTable");
	if(element->FirstChildElement(tempnewkey,false) == NULL)
	{
		ticpp::Element *langelement = element->FirstChildElement(tempkey);
		langelement->SetValue(tempnewkey);
		return true;
	}
	return false;
}

std::wstring StringTable::GetString(std::wstring key)
{
	std::string tempkey;
	std::wstring wstr;
	UnicodeToUTF8(key,tempkey);
	ticpp::Element *langelement = mLangFile.FirstChildElement("StringTable");
	ticpp::Element *langchildelement = langelement->FirstChildElement(tempkey,false);
	if(langchildelement)
	{
		std::string str;
		str = langchildelement->GetAttribute("value");
		UTF8ToUnicode(str,wstr);
	}
	return wstr;
}

bool StringTable::SetString(std::wstring key, std::wstring str)
{
	std::string tempkey;
	UnicodeToUTF8(key,tempkey);
	ticpp::Element *langelement = mLangFile.FirstChildElement("StringTable");
	ticpp::Element *langchildelement = langelement->FirstChildElement(tempkey,false);
	if(langchildelement)
	{
		std::string tempstr;
		UnicodeToUTF8(str,tempstr);
		langchildelement->SetAttribute("value", tempstr);
		return true;
	}
	return false;
}