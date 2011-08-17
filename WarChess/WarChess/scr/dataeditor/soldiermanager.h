#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"

class SoldierManager
{
public:
	SoldierManager();
	~SoldierManager();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetName(std::wstring id);
	std::wstring GetScriptName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetValue(std::wstring id);
	int GetInjury(std::wstring id);

	void AddSoldier(); //创建新的兵源
	void DelSoldier(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	bool SetValue(std::wstring id, int ivalue);
	bool SetInjury(std::wstring id, int injury);
};