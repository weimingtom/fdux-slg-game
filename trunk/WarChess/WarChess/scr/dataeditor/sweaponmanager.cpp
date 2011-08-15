// 副武器数据结构：
// <SweaponData>
//		<LongBow>
//			<Type type="Int" value="0"/>
//			<Value type="Int" value="10"/>
//			<Script type="String" value="none"/>
//			<Mesh type="String" value="bow.mesh"/>
//			<Mat type="String" value="Bow"/>
//			<MaxRange type="Int" value="3"/>
//			<MinRange type="Int" value="1"/>
//			<AniGroup type="String" value="bow"/>
//			<AttrModifer>
//				<Type type="Int" value="0"/>
//				<Attack type="Float" value="0.0"/>
//				<RangedAttack type="Float" value="6.0"/>
//				<Defence type="Float" value="0.0"/>
//				<Formation type="Float" value="0.0"/>
//				<Initiative type="Float" value="0.0"/>
//				<ActionPoint type="Float" value="0.0"/>
//				<Detection type="Float" value="0.0"/>
//				<Covert type="Float" value="0.0"/>
//				<Injury type="Float" value="0.0"/>
//				<Conter type="Float" value="0.0"/>
//			</AttrModifer>
//		</LongBow>

#include "sweaponmanager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

SWeaponManager::SWeaponManager()
{

}

SWeaponManager::~SWeaponManager()
{

}

bool SWeaponManager::LoadMod(std::wstring modName, std::wstring langName, bool editorMode)
{
	mModPath = L".\\..\\Mod\\" + modName + L"\\";

	std::wstring tempPath;
	tempPath = mModPath + L"data\\secondaryweapon.xml";

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
		tempPath = mModPath + L"data\\secondaryweapon.xml";
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

bool SWeaponManager::LoadLang(std::wstring langName)
{
	std::wstring tempPath;
	tempPath = mModPath + L"Lang\\" + langName + L"\\secondaryweapon.xml";

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

bool SWeaponManager::CreateDataFile()
{
	mDataFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "SweaponData" );
	mDataFile.LinkEndChild(decl);
	mDataFile.LinkEndChild(element);
	return true;
}

bool SWeaponManager::CreateLangFile()
{
	mLangFile.Clear();
	ticpp::Declaration * decl = new ticpp::Declaration( "1.0", "utf-8", "" );
	ticpp::Element * element = new ticpp::Element( "SweaponData" );
	mLangFile.LinkEndChild(decl);
	mLangFile.LinkEndChild(element);
	return true;
}

bool SWeaponManager::SaveData()
{
	if(mDataPath.size()> 0)
	{
		ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
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

bool SWeaponManager::SaveLang()
{
	if(mLangPath.size() > 0)
	{
		ticpp::Element *element = mLangFile.FirstChildElement("SweaponData");
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

int SWeaponManager::GetNum()
{
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
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

void SWeaponManager::AddSWeapon()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newwecondaryweapon%d",n);
	ticpp::Element *rootelement = mDataFile.FirstChildElement("SweaponData");
	while(rootelement->FirstChildElement(newid,false))
	{
		n = n + 1;
		sprintf_s(newid,20,"newwecondaryweapon%d",n);
	}
	ticpp::Element *element = new ticpp::Element(newid);

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

	element->LinkEndChild(typeElement);
	element->LinkEndChild(valueElement);
	element->LinkEndChild(scriptElement);
	element->LinkEndChild(meshElement);
	element->LinkEndChild(matElement);
	element->LinkEndChild(maxRangeElement);
	element->LinkEndChild(minRangeElement);
	element->LinkEndChild(aniElement);
	element->LinkEndChild(attrElement);

	rootelement->LinkEndChild(element);

	ticpp::Element *langrootelement = mLangFile.FirstChildElement("SweaponData");
	ticpp::Element *langelement = langrootelement->FirstChildElement(newid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(newid);

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
}

void SWeaponManager::DelSWeapon(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *dataelement = mDataFile.FirstChildElement("SweaponData");
	ticpp::Node *datachildelement = dataelement->FirstChildElement(tempid,false);
	if(datachildelement)
	{
		dataelement->RemoveChild(datachildelement);
	}
	ticpp::Element *langelement = mLangFile.FirstChildElement("SweaponData");
	ticpp::Node *langchildelement = langelement->FirstChildElement(tempid,false);
	if(langchildelement)
	{
		langelement->RemoveChild(langchildelement);
	}
}

std::wstring SWeaponManager::GetID(int index)
{
	int n = 0;
	std::string id;
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
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

std::wstring SWeaponManager::GetName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("SweaponData");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);

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
	ticpp::Element * nameElement = langelement->FirstChildElement("Name", false);
	name = nameElement->GetAttribute("value");
	std::wstring tempname;
	UTF8ToUnicode(name,tempname);
	return tempname;
}

std::wstring SWeaponManager::GetDescription(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mLangFile.FirstChildElement("SweaponData");
	ticpp::Element *langelement = element->FirstChildElement(tempid,false);
	if(langelement == NULL)
	{
		langelement = new ticpp::Element(tempid);

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
	ticpp::Element * describeElement = langelement->FirstChildElement("Describe", false);
	description = describeElement->GetAttribute("value");
	std::wstring tempdescription;
	UTF8ToUnicode(description,tempdescription);
	return tempdescription;
}

std::wstring SWeaponManager::GetScriptName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Script", false);
	std::string script;
	script = dataelement->GetAttribute("value");
	std::wstring tempscript;
	UTF8ToUnicode(script,tempscript);
	return tempscript;
}

int SWeaponManager::GetAttr(std::wstring id, BasicAttr attrType)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
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

int SWeaponManager::GetMaxRange(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("MaxRange", false);
	int maxrange = 0;
	dataelement->GetAttribute("value",&maxrange);
	return maxrange;
}

int SWeaponManager::GetMinRange(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("MinRange", false);
	int minrange = 0;
	dataelement->GetAttribute("value",&minrange);
	return minrange;
}

std::wstring SWeaponManager::GetMeshName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Mesh", false);
	std::string mesh;
	mesh = dataelement->GetAttribute("value");
	std::wstring tempmeshname;
	UTF8ToUnicode(mesh,tempmeshname);
	return tempmeshname;
}

std::wstring SWeaponManager::GetMatName(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Mat", false);
	std::string mat;
	mat = dataelement->GetAttribute("value");
	std::wstring tempmatname;
	UTF8ToUnicode(mat,tempmatname);
	return tempmatname;
}

std::wstring SWeaponManager::GetAniGroup(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("AniGroup", false);
	std::string aniGroup;
	aniGroup = dataelement->GetAttribute("value");
	std::wstring tempanigroup;
	UTF8ToUnicode(aniGroup,tempanigroup);
	return tempanigroup;
}

int SWeaponManager::GetSWeaponType(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Type", false);
	int swtypeint = 0;
	dataelement->GetAttribute("value",&swtypeint);
	return swtypeint;
}

int SWeaponManager::GetValue(std::wstring id)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Value", false);
	int ivalue = 0;
	dataelement->GetAttribute("value",&ivalue);
	return ivalue;
}

bool SWeaponManager::SetID(std::wstring oldid, std::wstring id)
{
	std::string tempoldid;
	UnicodeToUTF8(oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	//判断是否存在重复id
	if(element->FirstChildElement(tempid,false) == NULL)
	{
		ticpp::Element *dataelement = element->FirstChildElement(tempoldid);
		dataelement->SetValue(tempid);
		ticpp::Element *langelement = mLangFile.FirstChildElement("SweaponData");
		ticpp::Element *langchildelement = langelement->FirstChildElement(tempoldid,false);
		if(langchildelement == NULL)
		{
			langchildelement = new ticpp::Element(tempid);

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

bool SWeaponManager::SetName(std::wstring id, std::wstring name)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempname;
	UnicodeToUTF8(name,tempname);
	ticpp::Element *element = mLangFile.FirstChildElement("SweaponData");
	ticpp::Element *langelement = element->FirstChildElement(tempid, false)->FirstChildElement("Name", false);
	langelement->SetAttribute("value",tempname);
	return true;
}

bool SWeaponManager::SetDescription(std::wstring id, std::wstring descripition)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempdescripition;
	UnicodeToUTF8(descripition,tempdescripition);
	ticpp::Element *element = mLangFile.FirstChildElement("SweaponData");
	ticpp::Element *langelement = element->FirstChildElement(tempid, false)->FirstChildElement("Describe", false);
	langelement->SetAttribute("value", tempdescripition);
	return true;
}

bool SWeaponManager::SetScriptName(std::wstring id, std::wstring script)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempscript;
	UnicodeToUTF8(script,tempscript);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Script", false);
	dataelement->SetAttribute("value",tempscript);
	return true;
}

bool SWeaponManager::SetAttr(std::wstring id, BasicAttr attrType, int attr)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
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

bool SWeaponManager::SetMaxRange(std::wstring id, int maxrange)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("MaxRange", false);
	dataelement->SetAttribute("value",maxrange);
	return true;
}

bool SWeaponManager::SetMinRange(std::wstring id, int minrange)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("MinRange", false);
	dataelement->SetAttribute("value",minrange);
	return true;
}

bool SWeaponManager::SetMeshName(std::wstring id, std::wstring meshname)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempmeshname;
	UnicodeToUTF8(meshname,tempmeshname);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Mesh", false);
	dataelement->SetAttribute("value",tempmeshname);
	return true;
}

bool SWeaponManager::SetMatName(std::wstring id, std::wstring matname)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempmatname;
	UnicodeToUTF8(matname,tempmatname);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Mat", false);
	dataelement->SetAttribute("value",tempmatname);
	return true;
}

bool SWeaponManager::SetAniGroup(std::wstring id, std::wstring anigroup)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	std::string tempanigroup;
	UnicodeToUTF8(anigroup,tempanigroup);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("AniGroup", false);
	dataelement->SetAttribute("value",tempanigroup);
	return true;
}

bool SWeaponManager::SetSWeaponType(std::wstring id, int type)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Type", false);
	dataelement->SetAttribute("value",type);
	return true;
}

bool SWeaponManager::SetValue(std::wstring id, int ivalue)
{
	std::string tempid;
	UnicodeToUTF8(id,tempid);
	ticpp::Element *element = mDataFile.FirstChildElement("SweaponData");
	ticpp::Element *dataelement = element->FirstChildElement(tempid, false)->FirstChildElement("Value", false);
	dataelement->SetAttribute("value",ivalue);
	return true;
}