#pragma once

#include <ticpp.h>
#include <string>
#include "Modifier.h"


class SWeaponManager
{
public:
	SWeaponManager();
	~SWeaponManager();

	int GetNum(); //获取总数
	std::wstring GetID(int index);
	std::wstring GetName(std::wstring id);
	std::wstring GetDescription (std::wstring id);
	int GetAttr(std::wstring id,BasicAttr attrType);
	std::wstring GetScriptName(std::wstring id);
	int GetSWeaponType(std::wstring id);
	int GetMaxRange(std::wstring id);
	int GetMinRange(std::wstring id);
	std::wstring GetMeshName(std::wstring id);
	std::wstring GetMatName(std::wstring id);
	std::wstring GetAniGroup(std::wstring id);
	int GetValue(std::wstring id);

	void AddSWeapon();
	void DelSWeapon(std::wstring id);

	bool SetID(std::wstring oldid, std::wstring id);
	bool SetName(std::wstring id, std::wstring name);
	bool SetDescription(std::wstring id, std::wstring descripition);
	bool SetAttr(std::wstring id, BasicAttr attrType, int attr);
	bool SetScriptName(std::wstring id, std::wstring script);
	bool SetSWeaponType(std::wstring id, int type);
	bool SetMaxRange(std::wstring id, int maxRange);
	bool SetMinRange(std::wstring id, int minRange);
	bool SetMeshName(std::wstring id, std::wstring meshname);
	bool SetMatName(std::wstring id, std::wstring matname);
	bool SetAniGroup(std::wstring id, std::wstring anigroup);
	bool SetValue(std::wstring id, int ivalue);
};