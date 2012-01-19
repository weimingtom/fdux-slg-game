#pragma once

#include <string>

#include "squaddefine.h"

class Squad
{
public:
	Squad(std::string path, std::string srcpath);
	Squad(std::string path);
	virtual ~Squad();

	bool isInit() { return mInit; } 
private:
	bool mInit;
	std::string mPath;

public:
	std::string getPath() { return mPath; }

private:
	std::string mSquadId;

public:
	std::string getSquadId() { return mSquadId; }

//补给：装备更换
public:
	bool equipEquipment(enumtype equiptype, std::string equipid);
	void unloadEquipment(enumtype equiptype);

//补给：技能升级
public:
	bool learnSkill(enumtype skilltype, std::string skillid);
	void forgetSkill(std::string skillid);

//补给：随从更换
public:
	bool hireRetainer(std::string retainerid);
	void fireRetainer();

public:
	bool applyModifer(std::string modifierpath, std::string &modifierid);
	bool applyModifer(AttrModifier* modifier, std::string &modifierid);
	void removeModifier(std::string modifierid);
	
	bool addSkill(std::string skillid);
	void removeSkill(std::string skillid);


	bool applyEffect(std::string effectid, std::string &eid);
	void removeEffect(std::string eid);

public:
	virtual float getAttr(enumtype attrtype , enumtype calctype);

};