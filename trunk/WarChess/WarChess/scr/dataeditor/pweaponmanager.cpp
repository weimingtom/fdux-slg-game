// 载入及存储主武器数据
//
// 主武器数据格式：
// <PweaponData>
//		<HeavySword>
//			<Type type="Int" value="1"/>
//			<Value type="Int" value="10"/>
//			<Script type="String" value="none"/>
//			<Mesh type="String" value="soul.mesh"/>
//			<Mat type="String" value="soul"/>
//			<AniGroup type="String" value="1H2"/>
//			<AttrModifer>
//				<Type type="Int" value="0"/>
//				<Attack type="Float" value="5.0"/>
//				<RangedAttack type="Float" value="0.0"/>
//				<Defence type="Float" value="1.0"/>
//				<Formation type="Float" value="0.0"/>
//				<Initiative type="Float" value="3.0"/>
//				<ActionPoint type="Float" value="0.0"/>
//				<Detection type="Float" value="0.0"/>
//				<Covert type="Float" value="0.0"/>
//				<Injury type="Float" value="0.0"/>
//				<Conter type="Float" value="0.0"/>
//			</AttrModifer>
//		</HeavySword>
//
// 主武器字符串格式：
// <PweaponData>
//		<HeavySword>
//			<Name type="String" value="重剑"/>
//			<Describe type="String" value="重剑"/>
//		</HeavySword>

#include "pweaponmanager.h"
#include "DataManager.h"
#include "XMLManager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

PWeaponManager::PWeaponManager()
{

}

PWeaponManager::~PWeaponManager()
{

}

int PWeaponManager::GetNum()
{
	return DATAFILE()->CountData("PweaponData");
}

void PWeaponManager::AddPWeapon()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newpweapon%d", n);
	while(DATAFILE()->GetData("PweaponData", newid) != NULL)
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

	DATAFILE()->AddData("PweaponData", newPWeaponElement);

	ticpp::Element *newPWeaponLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newPWeaponLangElement->LinkEndChild(nameElement);
	newPWeaponLangElement->LinkEndChild(describeElement);

	DATAFILE()->AddLang("PweaponData", newPWeaponLangElement);
}

void PWeaponManager::DelPWeapon(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	DATAFILE()->RemoveData("PweaponData", tempid);
	DATAFILE()->RemoveLang("PweaponData", tempid);
}

std::wstring PWeaponManager::GetID(int _index)
{
	return DATAFILE()->GetDataID("PweaponData", _index);
}

std::wstring PWeaponManager::GetName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetLang("PweaponData", tempid);
	ticpp::Element *nameElement = armorElement->FirstChildElement("Name", false);
	std::string tempName;
	tempName = nameElement->GetAttribute("value");
	std::wstring name;
	UTF8ToUnicode(tempName, name);
	return name;
}

std::wstring PWeaponManager::GetDescription(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetLang("PweaponData", tempid);
	ticpp::Element *nameElement = armorElement->FirstChildElement("Describe", false);
	std::string tempDescription;
	tempDescription = nameElement->GetAttribute("value");
	std::wstring description;
	UTF8ToUnicode(tempDescription, description);
	return description;
}

std::wstring PWeaponManager::GetScriptName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *scriptElement = armorElement->FirstChildElement("Script", false);
	std::string tempScript;
	tempScript = scriptElement->GetAttribute("value");
	std::wstring script;
	UTF8ToUnicode(tempScript, script);
	return script;
}

int PWeaponManager::GetAttr(std::wstring _id, BasicAttr _attrType)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *attrElement = armorElement->FirstChildElement("AttrModifer", false);
	ticpp::Element *tempElement;
	int attr = 0;
	switch(_attrType)
	{
	case ATTR_ATTACK:
		tempElement = attrElement->FirstChildElement("Attack", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_RANGEDATTACK:
		tempElement = attrElement->FirstChildElement("RangedAttack", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_DEFENSE:
		tempElement = attrElement->FirstChildElement("Defence", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_FORMATION:
		tempElement = attrElement->FirstChildElement("Formation", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_INITIATIVE:
		tempElement = attrElement->FirstChildElement("Initiative", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_ACTIONPOINT:
		tempElement = attrElement->FirstChildElement("ActionPoint", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_DETECTION:
		tempElement = attrElement->FirstChildElement("Detection", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_COVERT:
		tempElement = attrElement->FirstChildElement("Covert", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_INJURY:
		tempElement = attrElement->FirstChildElement("Injury", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	case ATTR_COUNTER:
		tempElement = attrElement->FirstChildElement("Conter", false);
		tempElement->GetAttribute("value", &attr, false);
		break;
	default:
		return attr;
	}
	return attr;
}

int PWeaponManager::GetPWeaponType(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *typeElement = armorElement->FirstChildElement("Type", false);
	int type;
	typeElement->GetAttribute("value", &type, false);
	return type;
}

std::wstring PWeaponManager::GetMeshName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *scriptElement = armorElement->FirstChildElement("Mesh", false);
	std::string tempMesh;
	tempMesh = scriptElement->GetAttribute("value");
	std::wstring mesh;
	UTF8ToUnicode(tempMesh, mesh);
	return mesh;
}

std::wstring PWeaponManager::GetMatName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *scriptElement = armorElement->FirstChildElement("Mat", false);
	std::string tempMat;
	tempMat = scriptElement->GetAttribute("value");
	std::wstring mat;
	UTF8ToUnicode(tempMat, mat);
	return mat;
}

std::wstring PWeaponManager::GetAniGroup(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *scriptElement = armorElement->FirstChildElement("AniGroup", false);
	std::string tempMat;
	tempMat = scriptElement->GetAttribute("value");
	std::wstring mat;
	UTF8ToUnicode(tempMat, mat);
	return mat;
}

int PWeaponManager::GetValue(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("PweaponData", tempid);
	ticpp::Element *valueElement = armorElement->FirstChildElement("Value", false);
	int value;
	valueElement->GetAttribute("value", &value, false);
	return value;
}

bool PWeaponManager::SetID(std::wstring _oldid, std::wstring _id)
{
	std::string tempoldid;
	UnicodeToUTF8(_oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	ticpp::Element * element = DATAFILE()->GetData("PweaponData", tempid);
	if (element == NULL)
	{
		DATAFILE()->SetDataID("PweaponData", tempoldid, tempid);
		DATAFILE()->SetLangID("PweaponData", tempoldid, tempid);
	}
	return false;
}

bool PWeaponManager::SetName(std::wstring _id, std::wstring _name)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempname;
	UnicodeToUTF8(_name, tempname);
	return DATAFILE()->SetLang("PweaponData", tempid, "Name", tempname);
}

bool PWeaponManager::SetDescription(std::wstring _id, std::wstring _description)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempdescription;
	UnicodeToUTF8(_description, tempdescription);
	return DATAFILE()->SetLang("PweaponData", tempid, "Describe", tempdescription);
}

bool PWeaponManager::SetScriptName(std::wstring _id, std::wstring _script)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	std::string tempscript;
	UnicodeToUTF8(_script,tempscript);
	return DATAFILE()->SetDataStr("PweaponData", tempid, "Script", tempscript);
}

bool PWeaponManager::SetAttr(std::wstring _id, BasicAttr _attrType, int _attr)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	switch(_attrType)
	{
	case ATTR_ATTACK:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Attack", _attr);
	case ATTR_RANGEDATTACK:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "RangedAttack", _attr);
	case ATTR_DEFENSE:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Defence", _attr);
	case ATTR_FORMATION:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Formation", _attr);
	case ATTR_INITIATIVE:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Initiative", _attr);
	case ATTR_ACTIONPOINT:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "ActionPoint", _attr);
	case ATTR_DETECTION:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Detection", _attr);
	case ATTR_COVERT:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Covert", _attr);
	case ATTR_INJURY:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Injury", _attr);
	case ATTR_COUNTER:
		return DATAFILE()->SetDataAttr("PweaponData", tempid, "AttrModifer", "Conter", _attr);
	default:
		return false;
	}
}

bool PWeaponManager::SetMeshName(std::wstring _id, std::wstring _meshname)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempmesh;
	UnicodeToUTF8(_meshname,tempmesh);
	return DATAFILE()->SetDataStr("PweaponData", tempid, "Mesh", tempmesh);
}

bool PWeaponManager::SetMatName(std::wstring _id, std::wstring _matname)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempmat;
	UnicodeToUTF8(_matname,tempmat);
	return DATAFILE()->SetDataStr("PweaponData", tempid, "Mat", tempmat);
}

bool PWeaponManager::SetAniGroup(std::wstring _id, std::wstring _anigroup)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempani;
	UnicodeToUTF8(_anigroup,tempani);
	return DATAFILE()->SetDataStr("PweaponData", tempid, "AniGroup", tempani);
}

bool PWeaponManager::SetPWeaponType(std::wstring _id, int _type)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("PweaponData", tempid, "Type", _type);
}

bool PWeaponManager::SetValue(std::wstring _id, int _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("PweaponData", tempid, "Value", _value);
}