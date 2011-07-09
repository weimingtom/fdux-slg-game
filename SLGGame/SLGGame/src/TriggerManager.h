#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <string>

class BattleSquad;

class TriggerManager: public IISingleton<TriggerManager>
{
public:
	TriggerManager();
	~TriggerManager();

	std::string addTrigger(std::string trigertype, std::string file ,std::string func, std::string context);
	void removeTrigger(std::string id);

	void activeTrigger(std::string id);
	void disableTrigger(std::string id);

	void turnEnd(int turn, int team);
	void unitDead(BattleSquad* squad);
	void finishdeploy();
private:

};