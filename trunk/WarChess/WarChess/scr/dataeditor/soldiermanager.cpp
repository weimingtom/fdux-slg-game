// 载入及存储士兵数据
//
// 士兵数据格式：
// <SoilderData>
//		<WingsSoilder>
//			<Type type="Int" value="1"/>
//			<Value type="Int" value="10"/>
//			<Script type="String" value="none"/>
//			<AttrModifer>
//				<Type type="Int" value="0"/>
//				<Attack type="Float" value="3.0"/>
//				<RangedAttack type="Float" value="3.0"/>
//				<Defence type="Float" value="3.0"/>
//				<Formation type="Float" value="0.06"/>
//				<Initiative type="Float" value="1.0"/>
//				<ActionPoint type="Float" value="10.0"/>
//				<Detection type="Float" value="5.0"/>
//				<Covert type="Float" value="0.0"/>
//				<Injury type="Float" value="0.8"/>
//				<Conter type="Float" value="0.5"/>
//			</AttrModifer>
//			<Injury type="Int" value="1"/>
//		</WingsSoilder>
//
// 士兵字符串格式：
// <SoilderData>
//		<WingsSoilder>
//			<Name type="String" value="翼骑团战士"/>
//			<Describe type="String" value="翼骑团战士"/>
//		</WingsSoilder>

#include "soldiermanager.h"
#include "DataManager.h"
#include "XMLManager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

SoldierManager::SoldierManager()
{

}

SoldierManager::~SoldierManager()
{

}

int SoldierManager::GetNum()
{
	return DATAFILE()->CountData("SoilderData");
}

void SoldierManager::AddSoldier()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newsoldier%d", n);
	while(DATAFILE()->GetData("SoilderData", newid) != NULL)
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

	DATAFILE()->AddData("SoilderData", newSoldierElement);

	ticpp::Element *newSoldierLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newSoldierLangElement->LinkEndChild(nameElement);
	newSoldierLangElement->LinkEndChild(describeElement);

	DATAFILE()->AddLang("SoilderData", newSoldierLangElement);
}

void SoldierManager::DelSoldier(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	DATAFILE()->RemoveData("SoilderData", tempid);
	DATAFILE()->RemoveLang("SoilderData", tempid);
}

std::wstring SoldierManager::GetID(int _index)
{
	return DATAFILE()->GetDataID("SoilderData", _index);
}

std::wstring SoldierManager::GetName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetLang("SoilderData", tempid);
	ticpp::Element *nameElement = soldierElement->FirstChildElement("Name", false);
	std::string tempName;
	tempName = nameElement->GetAttribute("value");
	std::wstring name;
	UTF8ToUnicode(tempName, name);
	return name;
}

std::wstring SoldierManager::GetDescription(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetLang("SoilderData", tempid);
	ticpp::Element *nameElement = soldierElement->FirstChildElement("Describe", false);
	std::string tempDescription;
	tempDescription = nameElement->GetAttribute("value");
	std::wstring description;
	UTF8ToUnicode(tempDescription, description);
	return description;
}

std::wstring SoldierManager::GetScriptName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetData("SoilderData", tempid);
	ticpp::Element *scriptElement = soldierElement->FirstChildElement("Script", false);
	std::string tempScript;
	tempScript = scriptElement->GetAttribute("value");
	std::wstring script;
	UTF8ToUnicode(tempScript, script);
	return script;
}

int SoldierManager::GetAttr(std::wstring _id, BasicAttr _attrType)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetData("SoilderData", tempid);
	ticpp::Element *attrElement = soldierElement->FirstChildElement("AttrModifer", false);
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

int SoldierManager::GetValue(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetData("SoilderData", tempid);
	ticpp::Element *valueElement = soldierElement->FirstChildElement("Value", false);
	int value;
	valueElement->GetAttribute("value", &value, false);
	return value;
}

int SoldierManager::GetInjury(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *soldierElement = DATAFILE()->GetData("SoilderData", tempid);
	ticpp::Element *valueElement = soldierElement->FirstChildElement("Injury", false);
	int value;
	valueElement->GetAttribute("value", &value, false);
	return value;
}


bool SoldierManager::SetID(std::wstring _oldid, std::wstring _id)
{
	std::string tempoldid;
	UnicodeToUTF8(_oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	ticpp::Element * element = DATAFILE()->GetData("SoilderData", tempid);
	if (element == NULL)
	{
		DATAFILE()->SetDataID("SoilderData", tempoldid, tempid);
		DATAFILE()->SetLangID("SoilderData", tempoldid, tempid);
	}
	return false;
}

bool SoldierManager::SetName(std::wstring _id, std::wstring _name)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempname;
	UnicodeToUTF8(_name, tempname);
	return DATAFILE()->SetLang("SoilderData", tempid, "Name", tempname);
}

bool SoldierManager::SetDescription(std::wstring _id, std::wstring _description)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempdescription;
	UnicodeToUTF8(_description, tempdescription);
	return DATAFILE()->SetLang("SoilderData", tempid, "Describe", tempdescription);
}

bool SoldierManager::SetScriptName(std::wstring _id, std::wstring _script)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	std::string tempscript;
	UnicodeToUTF8(_script,tempscript);
	return DATAFILE()->SetDataStr("SoilderData", tempid, "Script", tempscript);
}

bool SoldierManager::SetAttr(std::wstring _id, BasicAttr _attrType, int _attr)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	switch(_attrType)
	{
	case ATTR_ATTACK:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Attack", _attr);
	case ATTR_RANGEDATTACK:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "RangedAttack", _attr);
	case ATTR_DEFENSE:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Defence", _attr);
	case ATTR_FORMATION:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Formation", _attr);
	case ATTR_INITIATIVE:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Initiative", _attr);
	case ATTR_ACTIONPOINT:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "ActionPoint", _attr);
	case ATTR_DETECTION:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Detection", _attr);
	case ATTR_COVERT:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Covert", _attr);
	case ATTR_INJURY:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Injury", _attr);
	case ATTR_COUNTER:
		return DATAFILE()->SetDataAttr("SoilderData", tempid, "AttrModifer", "Conter", _attr);
	default:
		return false;
	}
}

bool SoldierManager::SetValue(std::wstring _id, int _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("SoilderData", tempid, "Value", _value);
}

bool SoldierManager::SetInjury(std::wstring _id, int _injury)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("SoilderData", tempid, "Injury", _injury);
}