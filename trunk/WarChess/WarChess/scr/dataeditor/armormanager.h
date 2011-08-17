#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"


class ArmorManager
{
public:
	ArmorManager();
	~ArmorManager();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	std::wstring GetName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetScriptName(std::wstring id);
	int GetArmorType(std::wstring id);
	int GetValue(std::wstring id);

	void AddArmor();
	void DelArmor(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	bool SetArmorType(std::wstring id, int type);
	bool SetValue(std::wstring id, int ivalue);
};