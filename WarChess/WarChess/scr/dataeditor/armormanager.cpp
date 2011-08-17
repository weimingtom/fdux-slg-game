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
//
// 盔甲字符串格式：
// <ArmorData>
//		<[ArmorName]>
//			<Name type="String" value="重锁甲"/>
//			<Describe type="String" value="重锁甲"/>
//		</[ArmorName]>

#include "armormanager.h"
#include "DataManager.h"
#include "XMLManager.h"
#include "conversion.h"
#include "SquadEquip.h"
#include <Windows.h>

ArmorManager::ArmorManager()
{
}

ArmorManager::~ArmorManager()
{
}

// 返回盔甲总数

int ArmorManager::GetNum()
{
	return DATAFILE()->CountData("ArmorData");
}

// 添加一件盔甲

void ArmorManager::AddArmor()
{
	char newid[20];
	int n = 0;
	sprintf_s(newid, 20, "newarmor%d", n);
	while(DATAFILE()->GetData("ArmorData", newid) != NULL)
	{
		n = n + 1;
		sprintf_s(newid,20,"newhorse%d",n);
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

	DATAFILE()->AddData("ArmorData", newArmorElement);

	ticpp::Element *newArmorLangElement = new ticpp::Element(newid);

	ticpp::Element *nameElement = new ticpp::Element("Name");
	ticpp::Element *describeElement = new ticpp::Element("Describe");

	nameElement->SetAttribute("type", "String");
	nameElement->SetAttribute("value", "none");
	describeElement->SetAttribute("type", "String");
	describeElement->SetAttribute("value", "none");

	newArmorLangElement->LinkEndChild(nameElement);
	newArmorLangElement->LinkEndChild(describeElement);

	DATAFILE()->AddLang("ArmorData", newArmorLangElement);
}

// 删除一件盔甲

void ArmorManager::DelArmor(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	DATAFILE()->RemoveData("ArmorData", tempid);
	DATAFILE()->RemoveLang("ArmorData", tempid);
}

// 返回盔甲ID

std::wstring ArmorManager::GetID(int _index)
{	
	return DATAFILE()->GetDataID("ArmorData", _index);
}

// 返回盔甲名称

std::wstring ArmorManager::GetName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetLang("ArmorData", tempid);
	ticpp::Element *nameElement = armorElement->FirstChildElement("Name", false);
	std::string tempName;
	tempName = nameElement->GetAttribute("value");
	std::wstring name;
	UTF8ToUnicode(tempName, name);
	return name;
}

// 返回盔甲描述

std::wstring ArmorManager::GetDescription(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetLang("ArmorData", tempid);
	ticpp::Element *nameElement = armorElement->FirstChildElement("Describe", false);
	std::string tempDescription;
	tempDescription = nameElement->GetAttribute("value");
	std::wstring description;
	UTF8ToUnicode(tempDescription, description);
	return description;
}

// 返回盔甲脚本文件名

std::wstring ArmorManager::GetScriptName(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("ArmorData", tempid);
	ticpp::Element *scriptElement = armorElement->FirstChildElement("Script", false);
	std::string tempScript;
	tempScript = scriptElement->GetAttribute("value");
	std::wstring script;
	UTF8ToUnicode(tempScript, script);
	return script;
}

// 返回盔甲属性

int ArmorManager::GetAttr(std::wstring _id, BasicAttr _attrType)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("ArmorData", tempid);
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

// 返回盔甲类型

int ArmorManager::GetArmorType(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("ArmorData", tempid);
	ticpp::Element *typeElement = armorElement->FirstChildElement("Type", false);
	int type;
	typeElement->GetAttribute("value", &type, false);
	return type;
}

// 返回盔甲价值

int ArmorManager::GetValue(std::wstring _id)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	ticpp::Element *armorElement = DATAFILE()->GetData("ArmorData", tempid);
	ticpp::Element *valueElement = armorElement->FirstChildElement("Value", false);
	int value;
	valueElement->GetAttribute("value", &value, false);
	return value;
}

// 设定盔甲ID

bool ArmorManager::SetID(std::wstring _oldid, std::wstring _id)
{
	std::string tempoldid;
	UnicodeToUTF8(_oldid,tempoldid);
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	ticpp::Element * element = DATAFILE()->GetData("ArmorData", tempid);
	if (element == NULL)
	{
		DATAFILE()->SetDataID("ArmorData", tempoldid, tempid);
		DATAFILE()->SetLangID("ArmorData", tempoldid, tempid);
	}
	return false;
}

// 设定盔甲名称

bool ArmorManager::SetName(std::wstring _id, std::wstring _name)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempname;
	UnicodeToUTF8(_name, tempname);
	return DATAFILE()->SetLang("ArmorData", tempid, "Name", tempname);
}

// 设定盔甲描述

bool ArmorManager::SetDescription(std::wstring _id, std::wstring _description)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	std::string tempdescription;
	UnicodeToUTF8(_description, tempdescription);
	return DATAFILE()->SetLang("ArmorData", tempid, "Describe", tempdescription);
}

// 设定盔甲脚本文件名

bool ArmorManager::SetScriptName(std::wstring _id, std::wstring _script)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	std::string tempscript;
	UnicodeToUTF8(_script,tempscript);
	return DATAFILE()->SetDataStr("ArmorData", tempid, "Script", tempscript);
}

// 设定盔甲属性

bool ArmorManager::SetAttr(std::wstring _id, BasicAttr _attrType, int _attr)
{
	std::string tempid;
	UnicodeToUTF8(_id,tempid);
	switch(_attrType)
	{
	case ATTR_ATTACK:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Attack", _attr);
	case ATTR_RANGEDATTACK:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "RangedAttack", _attr);
	case ATTR_DEFENSE:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Defence", _attr);
	case ATTR_FORMATION:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Formation", _attr);
	case ATTR_INITIATIVE:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Initiative", _attr);
	case ATTR_ACTIONPOINT:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "ActionPoint", _attr);
	case ATTR_DETECTION:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Detection", _attr);
	case ATTR_COVERT:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Covert", _attr);
	case ATTR_INJURY:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Injury", _attr);
	case ATTR_COUNTER:
		return DATAFILE()->SetDataAttr("ArmorData", tempid, "AttrModifer", "Conter", _attr);
	default:
		return false;
	}
}

// 设定盔甲类型

bool ArmorManager::SetArmorType(std::wstring _id, int _type)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("ArmorData", tempid, "Type", _type);
}

// 设定盔甲价值

bool ArmorManager::SetValue(std::wstring _id, int _value)
{
	std::string tempid;
	UnicodeToUTF8(_id, tempid);
	return DATAFILE()->SetDataInt("ArmorData", tempid, "Value", _value);
}