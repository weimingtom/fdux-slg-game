// 载入及存储盔甲数据
//
// 盔甲数据格式：
// <ArmorData>
//		<[ArmorName]>
//			<Type type="Int" value="1"/>
//			<Value type="Int" value="10"/>
//			<Script type="String" value="none"/>
//			<AttrModifer>
//				<Type type="Int" value="0"/>
//				<Attack type="Float" value="0.0"/>
//				<RangedAttack type="Float" value="0.0"/>
//				<Defence type="Float" value="3.0"/>
//				<Formation type="Float" value="0.0"/>
//				<Initiative type="Float" value="0.0"/>
//				<ActionPoint type="Float" value="0.0"/>
//				<Detection type="Float" value="0.0"/>
//				<Covert type="Float" value="-1.0"/>
//				<Injury type="Float" value="0.0"/>
//				<Conter type="Float" value="0.0"/>
//			</AttrModifer>
//		</[ArmorName]>

// 盔甲字符串格式：
// <ArmorData>
//		<[ArmorName]>
//			<Name type="String" value="重锁甲"/>
//			<Describe type="String" value="重锁甲"/>
//		</[ArmorName]>

#include "armormanager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

ArmorManager::ArmorManager()
{

}

ArmorManager::~ArmorManager()
{

}

// 载入盔甲数据
// 先检索../Mod/modName/data/armor.xml
// 如果文件不存在且editorMode为真，则检索../Mod/common/data/armor.xml
// 如果editorMode为假，则创建../Mod/modName/data/armor.xml
// 函数永远返回真

bool ArmorManager::LoadMod(std::wstring modName, std::wstring langName, bool editorMode)
{
	mModPath = L".\\..\\Mod\\" + modName + L"\\";

	std::wstring tempPath;
	tempPath = mModPath + L"data\\armor.xml";

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
		tempPath = mModPath + L"data\\armor.xml";
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

// 载入盔甲字符串
// 先检索../Mod/modName/Lang/langName/armor.xml
// 如果文件不存在，则创建../Mod/modName/Lang/langName/armor.xml

bool ArmorManager::LoadLang(std::wstring langName)
{
	std::wstring tempPath;
	tempPath = mModPath + L"Lang\\" + langName + L"\\armor.xml";

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

// 创建空的盔甲数据

bool ArmorManager::CreateDataFile()
{
	mDataFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	//ticpp::Element * element = new ticpp::Element( "Armor" );
	ticpp::Element * element = new ticpp::Element("ArmorData");
	mDataFile.LinkEndChild(decl);
	mDataFile.LinkEndChild(element);

	//SaveData();
	return true;
}

// 创建空的盔甲字符串

bool ArmorManager::CreateLangFile()
{
	mLangFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	//ticpp::Element * element = new ticpp::Element( "Armor" );
	ticpp::Element * element = new ticpp::Element("ArmorData");
	mLangFile.LinkEndChild(decl);
	mLangFile.LinkEndChild(element);

	//SaveLang();
	return true;
}

// 存储盔甲数据

bool ArmorManager::SaveData()
{
	if(mDataPath.size()> 0)
	{
		//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
		ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
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

// 存储盔甲字符串

bool ArmorManager::SaveLang()
{
	if(mLangPath.size() > 0)
	{
		//ticpp::Element *element = mLangFile.FirstChildElement("Armor");
		ticpp::Element * element = mLangFile.FirstChildElement("ArmorData");
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

// 返回盔甲总数

int ArmorManager::GetNum()
{
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
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

// 添加一件盔甲

void ArmorManager::AddArmor()
{
	// newarmor后的数字从0开始，只要找到同名的盔甲，就将数字+1
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newarmor%d",n);
	//ticpp::Element *rootelement = mDataFile.FirstChildElement("Armor");
	ticpp::Element * rootelement = mDataFile.FirstChildElement("ArmorData");
	while(rootelement->FirstChildElement(newid,false))
	{
		n = n + 1;
		sprintf_s(newid,20,"newarmor%d",n);
	}
	ticpp::Element *element = new ticpp::Element(newid);
	/*
	element->SetAttribute("Attack",0);
	element->SetAttribute("RangedAttack",0);
	element->SetAttribute("Defence",0);
	element->SetAttribute("Formation",0);
	element->SetAttribute("Initiative",0);
	element->SetAttribute("ActionPoint",0);
	element->SetAttribute("Covert",0);
	element->SetAttribute("Script","");
	element->SetAttribute("ArmorType",ARMOR_NONE);
	element->SetAttribute("Value",0);
    */

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

	element->LinkEndChild(typeElement);
	element->LinkEndChild(valueElement);
	element->LinkEndChild(scriptElement);
	element->LinkEndChild(attrElement);

	rootelement->LinkEndChild(element);

	//ticpp::Element *langrootelement = mLangFile.FirstChildElement("Armor");
	ticpp::Element * langrootelement = mLangFile.FirstChildElement("ArmorData");
	ticpp::Element *langelement = langrootelement->FirstChildElement(newid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(newid);
		/*
		langelement->SetAttribute("Name",newid);
		langelement->SetText("Please add a description.");
		*/

		ticpp::Element * nameElement = new ticpp::Element("Name");
		ticpp::Element * describeElement = new ticpp::Element("Describe");

		nameElement->SetAttribute("type", "String");
		nameElement->SetAttribute("value", "none");
		describeElement->SetAttribute("type", "String");
		describeElement->SetAttribute("value", "none");

		langelement->LinkEndChild(nameElement);
		langelement->LinkEndChild(describeElement);

		langrootelement->LinkEndChild(langelement);
	}

	//SaveData();
	//SaveLang();
}

void ArmorManager::DelArmor(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *dataelement = mDataFile.FirstChildElement("Armor");
	ticpp::Element * dataelement = mDataFile.FirstChildElement("ArmorData");
	ticpp::Node *datachildelement = dataelement->FirstChildElement(tempid,false);
	if(datachildelement)
	{
		dataelement->RemoveChild(datachildelement);
	}
	//ticpp::Element *langelement = mLangFile.FirstChildElement("Armor");
	ticpp::Element * langelement = mLangFile.FirstChildElement("ArmorData");
	ticpp::Node *langchildelement = langelement->FirstChildElement(tempid,false);
	if(langchildelement)
	{
		langelement->RemoveChild(langchildelement);
	}

	//SaveData();
	//SaveLang();
}

std::wstring ArmorManager::GetID(int index)
{
	int n = 0;
	std::string id;
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
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

std::wstring ArmorManager::GetName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mLangFile.FirstChildElement("Armor");
	ticpp::Element * element = mLangFile.FirstChildElement("ArmorData");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);
		/*
		langelement->SetAttribute("Name",tempid);
		langelement->SetText("Please add a description.");
		*/

		ticpp::Element * nameElement = new ticpp::Element("Name");
		ticpp::Element * describeElement = new ticpp::Element("Describe");

		nameElement->SetAttribute("type", "String");
		nameElement->SetAttribute("value", "none");
		describeElement->SetAttribute("type", "String");
		describeElement->SetAttribute("value", "none");

		langelement->LinkEndChild(nameElement);
		langelement->LinkEndChild(describeElement);

		element->LinkEndChild(langelement);
	}
	std::string name;
	//name = langelement->GetAttribute("Name");
	ticpp::Element * nameElement = langelement->FirstChildElement("Name", false);
	name = nameElement->GetAttribute("value");
	std::wstring tempname;
	UTF8ToUnicode(name,tempname);
	return tempname;
}

std::wstring ArmorManager::GetDescription(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mLangFile.FirstChildElement("Armor");
	ticpp::Element * element = mLangFile.FirstChildElement("ArmorData");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);
		/*
		langelement->SetAttribute("Name",tempid);
		langelement->SetText("Please add a description.");
		*/

		ticpp::Element * nameElement = new ticpp::Element("Name");
		ticpp::Element * describeElement = new ticpp::Element("Describe");

		nameElement->SetAttribute("type", "String");
		nameElement->SetAttribute("value", "none");
		describeElement->SetAttribute("type", "String");
		describeElement->SetAttribute("value", "none");

		langelement->LinkEndChild(nameElement);
		langelement->LinkEndChild(describeElement);

		element->LinkEndChild(langelement);
	}
	std::string description;
	//description = langelement->GetText();
	ticpp::Element * describeElement = langelement->FirstChildElement("Describe", false);
	description = describeElement->GetAttribute("value");
	std::wstring tempdescription;
	UTF8ToUnicode(description,tempdescription);
	return tempdescription;
}

std::wstring ArmorManager::GetScriptName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false);
	std::string script;
	//script = dataelement->GetAttribute("Script");
	ticpp::Element * scriptElement = dataelement->FirstChildElement("Script", false);
	script = scriptElement->GetAttribute("value");
	std::wstring tempscript;
	UTF8ToUnicode(script,tempscript);
	return tempscript;
}

int ArmorManager::GetAttr(std::wstring id, BasicAttr attrType)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("AttrModifer", false);
	ticpp::Element * tempElement;
	int attr = 0;
	switch(attrType)
	{
	case ATTR_ATTACK:
		//dataelement->GetAttribute("Attack",&attr);
		tempElement = dataelement->FirstChildElement("Attack", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_RANGEDATTACK:
		//dataelement->GetAttribute("RangedAttack",&attr);
		tempElement = dataelement->FirstChildElement("RangedAttack", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_DEFENSE:
		//dataelement->GetAttribute("Defence",&attr);
		tempElement = dataelement->FirstChildElement("Defence", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_FORMATION:
		//dataelement->GetAttribute("Formation",&attr);
		tempElement = dataelement->FirstChildElement("Formation", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_INITIATIVE:
		//dataelement->GetAttribute("Initiative",&attr);
		tempElement = dataelement->FirstChildElement("Initiative", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_ACTIONPOINT:
		//dataelement->GetAttribute("ActionPoint",&attr);
		tempElement = dataelement->FirstChildElement("ActionPoint", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_DETECTION:
		tempElement = dataelement->FirstChildElement("Detection", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_COVERT:
		//dataelement->GetAttribute("Covert",&attr);
		tempElement = dataelement->FirstChildElement("Covert", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_INJURY:
		tempElement = dataelement->FirstChildElement("Injury", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_COUNTER:
		tempElement = dataelement->FirstChildElement("Conter", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	default:
		return attr;
	}
	return attr;
}

int ArmorManager::GetArmorType(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false);
	int atypeint = 0;
	//dataelement->GetAttribute("ArmorType",&atypeint);
	ticpp::Element * tempElement = dataelement->FirstChildElement("Type", false);
	tempElement->GetAttribute("value", &atypeint);
	return atypeint;
}


int ArmorManager::GetValue(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false);
	int ivalue = 0;
	//dataelement->GetAttribute("Value",&ivalue);
	ticpp::Element * tempElement = dataelement->FirstChildElement("Value", false);
	tempElement->GetAttribute("value", &ivalue);
	return ivalue;
}

bool ArmorManager::SetID(std::wstring oldid, std::wstring id)
{
	std::string tempoldid;
	UnicodeToUTF8(oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	//判断是否存在重复id
	if(element->FirstChildElement(tempid,false) == NULL)
	{
		ticpp::Element *dataelement = element->FirstChildElement(tempoldid, false);
		dataelement->SetValue(tempid);
		//ticpp::Element *langelement = mLangFile.FirstChildElement("Armor");
		ticpp::Element * langelement = mLangFile.FirstChildElement("ArmorData");
		ticpp::Element *langchildelement = langelement->FirstChildElement(tempoldid,false);
		if(langchildelement == NULL)
		{
			langchildelement = new ticpp::Element(tempid);
			/*
			langchildelement->SetAttribute("Name",tempid);
			langchildelement->SetText("Please add a description.");
			*/

			ticpp::Element * nameElement = new ticpp::Element("Name");
			ticpp::Element * describeElement = new ticpp::Element("Describe");

			nameElement->SetAttribute("type", "String");
			nameElement->SetAttribute("value", "none");
			describeElement->SetAttribute("type", "String");
			describeElement->SetAttribute("value", "none");

			langchildelement->LinkEndChild(nameElement);
			langchildelement->LinkEndChild(describeElement);

			langelement->LinkEndChild(langchildelement);
		}
		else
			langchildelement->SetValue(tempid);
		return true;
	}
	return false;
}

bool ArmorManager::SetName(std::wstring id, std::wstring name)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempname;
	UnicodeToUTF8(name,tempname);
	//ticpp::Element *element = mLangFile.FirstChildElement("Armor");
	//ticpp::Element *langelement = element->FirstChildElement(tempid);
	//langelement->SetAttribute("Name", tempname);
	ticpp::Element * element = mLangFile.FirstChildElement("ArmorData");
	ticpp::Element *langelement = element->FirstChildElement(tempid, false)->FirstChildElement("Name", false);
	langelement->SetAttribute("value",tempname);
	return true;
}

bool ArmorManager::SetDescription(std::wstring id, std::wstring descripition)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempdescripition;
	UnicodeToUTF8(descripition,tempdescripition);
	//ticpp::Element *element = mLangFile.FirstChildElement("Armor");
	//ticpp::Element *langelement = element->FirstChildElement(tempid);
	//langelement->SetText(tempdescripition);
	ticpp::Element * element = mLangFile.FirstChildElement("ArmorData");
	ticpp::Element * langelement = element->FirstChildElement(tempid, false)->FirstChildElement("Describe", false);
	langelement->SetAttribute("value", tempdescripition);
	return true;
}

bool ArmorManager::SetScriptName(std::wstring id, std::wstring script)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempscript;
	UnicodeToUTF8(script,tempscript);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	//ticpp::Element *dataelement = element->FirstChildElement(tempid);
	//dataelement->SetAttribute("Script",tempscript);
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element * dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Script", false);
	dataelement->SetAttribute("value", tempscript);
	return true;
}

bool ArmorManager::SetAttr(std::wstring id, BasicAttr attrType, int attr)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("AttrModifer", false);
	ticpp::Element * tempElement;
	switch(attrType)
	{
	case ATTR_ATTACK:
		//dataelement->SetAttribute("Attack",attr);
		tempElement = dataelement->FirstChildElement("Attack", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_RANGEDATTACK:
		//dataelement->SetAttribute("RangedAttack",attr);
		tempElement = dataelement->FirstChildElement("RangedAttack", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_DEFENSE:
		//dataelement->SetAttribute("Defence",attr);
		tempElement = dataelement->FirstChildElement("Defence", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_FORMATION:
		//dataelement->SetAttribute("Formation",attr);
		tempElement = dataelement->FirstChildElement("Formation", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_INITIATIVE:
		//dataelement->SetAttribute("Initiative",attr);
		tempElement = dataelement->FirstChildElement("Initiative", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_ACTIONPOINT:
		//dataelement->SetAttribute("ActionPoint",attr);
		tempElement = dataelement->FirstChildElement("ActionPoint", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_DETECTION:
		tempElement = dataelement->FirstChildElement("Detection", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_COVERT:
		//dataelement->SetAttribute("Covert",attr);
		tempElement = dataelement->FirstChildElement("Covert", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_INJURY:
		tempElement = dataelement->FirstChildElement("Injury", false);
		tempElement->SetAttribute("value", attr);
		break;
	case ATTR_COUNTER:
		tempElement = dataelement->FirstChildElement("Conter", false);
		tempElement->SetAttribute("value", attr);
		break;
	default:
		return false;
	}
	return true;
}

bool ArmorManager::SetArmorType(std::wstring id, int type)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	//ticpp::Element *dataelement = element->FirstChildElement(tempid);
	//dataelement->SetAttribute("ArmorType",type);
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element * dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Type", false);
	dataelement->SetAttribute("value", type);
	return true;
}

bool ArmorManager::SetValue(std::wstring id, int ivalue)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	//ticpp::Element *element = mDataFile.FirstChildElement("Armor");
	//ticpp::Element *dataelement = element->FirstChildElement(tempid);
	//dataelement->SetAttribute("Value",ivalue);
	ticpp::Element * element = mDataFile.FirstChildElement("ArmorData");
	ticpp::Element * dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Value", false);
	dataelement->SetAttribute("value", ivalue);
	return true;
}