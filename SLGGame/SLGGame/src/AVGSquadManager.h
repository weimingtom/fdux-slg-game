#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>
#include <vector>

#include "squaddefine.h"

class AVGSquadManager:public IISingleton<AVGSquadManager>
{
public:
	AVGSquadManager();
	~AVGSquadManager();

	bool addSquad(std::string uid, std::string id, std::string path);
	bool equipEquipment(std::string path, EquipmentType type, std::string id);
	bool learnSkill(std::string path,std::string id);
	bool applyModifer(std::string path, std::string modifierpath, std::string &modifierid);
	void removeModifier(std::string path,std::string modifierid);
	bool applyModifer(std::string path, AttrModifier* modifier, std::string &modifierid);
	bool applyEffect(std::string path, std::string id, std::string &effectid);
	void removeEffect(std::string path,std::string effectid);
	bool getSquadAttr(std::string path, AttrType attrtype, AttrCalcType calctype, float &val);
private:
};