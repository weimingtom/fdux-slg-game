#pragma once

#include <string>
#include <map>

#include "squaddefine.h"
#include "DataLibrary.h"

struct LuaTempContext;

#define INTVAL(a) int get##a() \
	{ \
		int val = 0; \
		DataLibrary::getSingleton().getData(getPath() + "/" + #a, val); \
		return val; \
	} \
	void set##a(int val) \
	{ \
		DataLibrary::getSingleton().setData(getPath() + "/" + #a, val); \
	}

#define FLOATVAL(a) float get##a() \
	{ \
		float val = 0.0f; \
		DataLibrary::getSingleton().getData(getPath() + "/" + #a, val); \
		return val; \
	} \
	void set##a(float val) \
	{ \
		DataLibrary::getSingleton().setData(getPath() + "/" + #a, val); \
	}

#define STRVAL(a) std::string get##a() \
	{ \
		std::string val(""); \
		DataLibrary::getSingleton().getData(getPath() + "/" + #a, val); \
		return val; \
	} \
	void set##a(std::string val) \
	{ \
		DataLibrary::getSingleton().setData(getPath() + "/" + #a, val); \
	}

class Squad
{
public:
	Squad(std::string path);
	virtual ~Squad();

	virtual bool init(std::string srcpath);
	virtual bool init();
protected:
	std::string mPath;

public:
	std::string getPath() { return mPath; }

protected:
	std::string mSquadId;

public:
	std::string getSquadId() { return mSquadId; }

//补给：装备更换
public:
	bool equipEquipment(int equiptype, std::string equipid);
	void unloadEquipment(int equiptype);
	std::string getEquipment(int equiptype);

//补给：技能升级
public:
	bool learnSkill(int skilltype, std::string skillid);
	void forgetSkill(std::string skillid);

	void addExp(int exp);

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
	int getSkillLevel(std::string skillid);


	bool applyEffect(std::string effectid, std::string &eid);
	void removeEffect(std::string eid);
	int getEffectLevel(std::string eid);
	int getEffectLevelByName(std::string effectname);

public:
	virtual float getAttr(int attrtype , int calctype);

//触发器
public:
	std::string addTrigger(std::string trigertype, std::string file ,std::string func, std::string context);
	void removeTrigger(std::string tid);

	void activeTrigger(std::string tid);
	void disableTrigger(std::string tid);

protected:
	void Trigger(std::string triggertype, LuaTempContext *tempcontext);


//获取属性
public:
	std::map<std::string, int> getSkillTable();

public:
	INTVAL(Type);
	INTVAL(SquadType);

	STRVAL(Name);

	INTVAL(UnitNum);
	INTVAL(Level);
	INTVAL(Exp);
	INTVAL(SkillPointAction);
	INTVAL(SkillPointPassive);
	INTVAL(SkillPointEquip);

	STRVAL(SoilderId);
	STRVAL(HorseId);
	STRVAL(PweaponId);
	STRVAL(ShieldId);
	STRVAL(SweaponId);
	STRVAL(ArmorId);
	STRVAL(LeaderId);
	STRVAL(RetainerId);
};