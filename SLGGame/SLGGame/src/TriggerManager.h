#pragma once

#include "iisingleton.hpp"
using namespace izayoi;

#include <map>
#include <string>

class BattleSquad;
class BattleState;

class TriggerContext
{
public:
	TriggerContext(std::string type);
	~TriggerContext();
	void SetContext(std::string key, std::string val);
	void SetContext(std::string key, int val);
	void SetContext(std::string key, float val);
private:
	std::string m_TriggerType;
	std::map<std::string, std::string> m_ContextMapS;
	std::map<std::string, int> m_ContextMapI;
	std::map<std::string, float> m_ContextMapF;
	friend class TriggerManager;
};

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

	void setBattleState(BattleState* battlestate);
	void changeState(int statetype, std::string arg);

	void Trigger(std::string path, TriggerContext* triggercontext);
private:
	BattleState* mBattleState;
};