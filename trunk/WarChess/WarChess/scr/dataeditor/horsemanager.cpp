//Type Value Script AttrModifer
//Attack RangedAttack Defence Formation Initiative ActionPoint Covert

#include "horsemanager.h"
#include "DataManager.h"
#include "XMLManager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

HorseManager::HorseManager()
{

}

HorseManager::~HorseManager()
{

}

int HorseManager::GetNum()
{
	return DATAFILE()->CountData("HorseData");
}

void HorseManager::AddHorse()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid,20,"newhorse%d",n);
	while(DATAFILE()->GetData("HorseData", newid) != NULL)
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

	DATAFILE()->AddData("HorseData", newHorseElement);

	ticpp::Element *newHorseLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newHorseLangElement->LinkEndChild(nameElement);
	newHorseLangElement->LinkEndChild(describeElement);

	DATAFILE()->AddLang("HorseData", newHorseLangElement);
}

void HorseManager::DelHorse(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	DATAFILE()->RemoveData("HorseData", tempid);
	DATAFILE()->RemoveLang("HorseData", tempid);
}

std::wstring HorseManager::GetID(int _index)
{
	return DATAFILE()->GetDataID("HorseData", _index);
}

std::wstring HorseManager::GetName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *horseElement = DATAFILE()->GetLang("HorseData", tempid);
	ticpp::Element *nameElement = horseElement->FirstChildElement("Name", false);
	std::string tempName;
	tempName = nameElement->GetAttribute("value");
	std::wstring name;
	UTF8ToUnicode(tempName, name);
	return name;
}

std::wstring HorseManager::GetDescription(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *horseElement = DATAFILE()->GetLang("HorseData", tempid);
	ticpp::Element *nameElement = horseElement->FirstChildElement("Describe", false);
	std::string tempName;
	tempName = nameElement->GetAttribute("value");
	std::wstring name;
	UTF8ToUnicode(tempName, name);
	return name;
}

std::wstring HorseManager::GetScriptName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *horseElement = DATAFILE()->GetData("HorseData", tempid);
	ticpp::Element *scriptElement = horseElement->FirstChildElement("Script", false);
	std::string tempScript;
	tempScript = scriptElement->GetAttribute("value");
	std::wstring script;
	UTF8ToUnicode(tempScript, script);
	return script;
}

int HorseManager::GetAttr(std::wstring _id, BasicAttr _attrType)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *horseElement = DATAFILE()->GetData("HorseData", tempid);
	ticpp::Element *attrElement = horseElement->FirstChildElement("AttrModifer", false);
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

int HorseManager::GetValue(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *horseElement = DATAFILE()->GetData("HorseData", tempid);
	ticpp::Element *valueElement = horseElement->FirstChildElement("Value", false);
	int value;
	valueElement->GetAttribute("value", &value, false);
	return value;
}

bool HorseManager::SetID(std::wstring _oldid, std::wstring _id)
{
	std::string tempoldid;
	UnicodeToUTF8(_oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	ticpp::Element * element = DATAFILE()->GetData("HorseData", tempid);
	if (element == NULL)
	{
		DATAFILE()->SetDataID("HorseData", tempoldid, tempid);
		DATAFILE()->SetLangID("HorseData", tempoldid, tempid);
	}
	return false;
}

bool HorseManager::SetName(std::wstring _id, std::wstring _name)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempname;
	UnicodeToUTF8(_name, tempname);
	return DATAFILE()->SetLang("HorseData", tempid, "Name", tempname);
}

bool HorseManager::SetDescription(std::wstring _id, std::wstring _description)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempdescription;
	UnicodeToUTF8(_description, tempdescription);
	return DATAFILE()->SetLang("HorseData", tempid, "Describe", tempdescription);
}

bool HorseManager::SetScriptName(std::wstring _id, std::wstring _script)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	std::string tempscript;
	UnicodeToUTF8(_script,tempscript);
	return DATAFILE()->SetDataStr("HorseData", tempid, "Script", tempscript);
}

bool HorseManager::SetAttr(std::wstring _id, BasicAttr _attrType, int _attr)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	switch(_attrType)
	{
	case ATTR_ATTACK:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Attack", _attr);
	case ATTR_RANGEDATTACK:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "RangedAttack", _attr);
	case ATTR_DEFENSE:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Defence", _attr);
	case ATTR_FORMATION:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Formation", _attr);
	case ATTR_INITIATIVE:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Initiative", _attr);
	case ATTR_ACTIONPOINT:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "ActionPoint", _attr);
	case ATTR_DETECTION:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Detection", _attr);
	case ATTR_COVERT:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Covert", _attr);
	case ATTR_INJURY:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Injury", _attr);
	case ATTR_COUNTER:
		return DATAFILE()->SetDataAttr("HorseData", tempid, "AttrModifer", "Conter", _attr);
	default:
		return false;
	}
}

bool HorseManager::SetValue(std::wstring _id, int _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("HorseData", tempid, "Value", _value);
}