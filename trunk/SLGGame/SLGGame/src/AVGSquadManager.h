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
	void modifyMorale(std::string id, int morale);

	bool equipEquipment(std::string path, EquipmentType type, std::string id);

	bool learnSkill(std::string path,std::string id);

	bool applyModifer(std::string path, std::string modifierpath, std::string &modifierid);
	void removeModifier(std::string path,std::string modifierid);
	bool applyModifer(std::string path, AttrModifier* modifier, std::string &modifierid);
	
	bool applyEffect(std::string path, std::string id, std::string &effectid);
	void removeEffect(std::string path,std::string effectid);
	
	bool getSquadAttr(std::string path, AttrType attrtype, AttrCalcType calctype, float &val);
	
	bool applyParticle(std::string path,UnitType unittype, std::string particle, std::string &particleid);
	void removeParticle(std::string path,std::string particleid);
	
	bool addTrigger(std::string path,std::string trigertype, std::string file ,std::string func, std::string context, std::string &triggerid);
	void removeTrigger(std::string path,std::string triggerid);
	void activeTrigger(std::string path,std::string triggerid);
	void disableTrigger(std::string path,std::string triggerid);
private:
};