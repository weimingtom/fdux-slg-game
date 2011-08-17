#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"

class ShieldManager
{
public:
	ShieldManager();
	~ShieldManager();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	std::wstring GetName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetScriptName(std::wstring id);
	std::wstring GetMeshName(std::wstring id);
	std::wstring GetMatName(std::wstring id);
	int GetValue(std::wstring id);

	void AddShield();
	void DelShield(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	bool SetMeshName(std::wstring id, std::wstring meshname);
	bool SetMatName(std::wstring id, std::wstring matname);
	bool SetValue(std::wstring id, int ivalue);
};