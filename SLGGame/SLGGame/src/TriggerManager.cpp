#include "TriggerManager.h"

#include "DataLibrary.h"
#include "BattleSquad.h"
#include "BattleState.h"
#include "LuaSystem.h"
#include "boost/format.hpp"

TriggerContext::TriggerContext(std::string type)
{
	m_TriggerType = type;
}
TriggerContext::~TriggerContext()
{

}
void TriggerContext::SetContext(std::string key, std::string val)
{
	m_ContextMapS[key] = val;
}

void TriggerContext::SetContext(std::string key, int val)
{
	m_ContextMapI[key] = val;
}

void TriggerContext::SetContext(std::string key, float val)
{
	m_ContextMapF[key] = val;
}

TriggerManager::TriggerManager()
{

}
TriggerManager::~TriggerManager()
{

}

std::string TriggerManager::addTrigger(std::string trigertype, std::string file ,std::string func, std::string context)
{
	int newid = 0;
	int test;
	while(DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Trigger/T%1%")%newid),test,true))
		newid++;
	DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/T%1%")%newid),0);
	DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/T%1%/type")%newid),trigertype);
	DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/T%1%/file")%newid),file);
	DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/T%1%/func")%newid),func);
	DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/T%1%/context")%newid),context);
	return std::string("T") + Ogre::StringConverter::toString(newid);
}

void TriggerManager::removeTrigger(std::string id)
{
	std::string particlepath = std::string("GameData/BattleData/Trigger/") + id;
	DataLibrary::getSingleton().delNode(particlepath);
}

void TriggerManager::activeTrigger(std::string id)
{
	int test;
	if(DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Trigger/%1%")%id),test,true))
	{
		DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/%1%")%id),1);
	}
}

void TriggerManager::disableTrigger(std::string id)
{
	int test;
	if(DataLibrary::getSingleton().getData(str(boost::format("GameData/BattleData/Trigger/%1%")%id),test,true))
	{
		DataLibrary::getSingleton().setData(str(boost::format("GameData/BattleData/Trigger/%1%")%id),0);
	}
}

void TriggerManager::unitDead(BattleSquad* squad)
{
// 	DataLibrary* datalib = DataLibrary::getSingletonPtr();
// 	std::vector<std::string> triggerlist;
// 	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
// 	if(triggerlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
// 		{
// 			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
// 			int active;
// 			datalib->getData(datapath ,active);
// 			if(!active)
// 				continue;
// 			std::string type;
// 			datalib->getData(datapath + std::string("/type"),type);
// 			if(type != "UnitDead")
// 				continue;
// 			std::string context,filename,funcname;
// 			datalib->getData(datapath + std::string("/file"),filename);
// 			datalib->getData(datapath + std::string("/func"),funcname);
// 			datalib->getData(datapath + std::string("/context"),context);
// 			datalib->setData(context + std::string("/squad"),squad->getId());
// 			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
// 		}
// 	}
	TriggerContext* trigger = new TriggerContext("UnitDead");
	trigger->SetContext("squad",squad->getSquadId());
	Trigger("GameData/BattleData",trigger);
}

void TriggerManager::turnEnd(int turn, int team)
{
// 	DataLibrary* datalib = DataLibrary::getSingletonPtr();
// 	std::vector<std::string> triggerlist;
// 	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
// 	if(triggerlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
// 		{
// 			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
// 			int active;
// 			datalib->getData(datapath,active);
// 			if(!active)
// 				continue;
// 			std::string type;
// 			datalib->getData(datapath + std::string("/type"),type);
// 			if(type != "TurnEnd")
// 				continue;
// 			std::string context,filename,funcname;
// 			datalib->getData(datapath + std::string("/file"),filename);
// 			datalib->getData(datapath + std::string("/func"),funcname);
// 			datalib->getData(datapath + std::string("/context"),context);
// 			datalib->setData(context + std::string("/trun"),turn);
// 			datalib->setData(context + std::string("/team"),team);
// 			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
// 		}
// 	}
	TriggerContext* trigger = new TriggerContext("TurnEnd");
	trigger->SetContext("trun",turn);
	trigger->SetContext("team",team);
	Trigger("GameData/BattleData",trigger);
}

void TriggerManager::finishdeploy()
{
// 	DataLibrary* datalib = DataLibrary::getSingletonPtr();
// 	std::vector<std::string> triggerlist;
// 	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
// 	if(triggerlist.size()>0)
// 	{
// 		std::vector<std::string>::iterator ite;
// 		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
// 		{
// 			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
// 			int active;
// 			datalib->getData(datapath,active);
// 			if(!active)
// 				continue;
// 			std::string type;
// 			datalib->getData(datapath + std::string("/type"),type);
// 			if(type != "FinishDeploy")
// 				continue;
// 			std::string context,filename,funcname;
// 			datalib->getData(datapath + std::string("/file"),filename);
// 			datalib->getData(datapath + std::string("/func"),funcname);
// 			datalib->getData(datapath + std::string("/context"),context);
// 			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
// 		}
// 	}
	TriggerContext* trigger = new TriggerContext("FinishDeploy");
	Trigger("GameData/BattleData",trigger);
}

void TriggerManager::setBattleState(BattleState* battlestate)
{
	mBattleState = battlestate;
}
void TriggerManager::changeState(int statetype, std::string arg)
{
	if(mBattleState)
		mBattleState->setNextState(statetype,arg);
}

void TriggerManager::Trigger(std::string path, TriggerContext* triggercontext)
{
	if(triggercontext == NULL)
		return;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> triggerlist;
	triggerlist = datalib->getChildList(path + std::string("/Trigger"));
	if(triggerlist.size()>0)
	{
		std::vector<std::string>::iterator ite;
		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
		{
			std::string datapath = path + std::string("/Trigger/") + (*ite);
			int active;
			datalib->getData(datapath,active);
			if(!active)
				continue;
			std::string type;
			datalib->getData(datapath + std::string("/type"),type);
			if(type != triggercontext->m_TriggerType)
				continue;
			std::string context,filename,funcname;
			datalib->getData(datapath + std::string("/file"),filename);
			datalib->getData(datapath + std::string("/func"),funcname);
			datalib->getData(datapath + std::string("/context"),context);
			std::map<std::string, std::string>::iterator ites;
			for(ites = triggercontext->m_ContextMapS.begin();ites != triggercontext->m_ContextMapS.end(); ites++)
			{
				datalib->setData(context + std::string("/") + ites->first,ites->second);
			}
			std::map<std::string, int>::iterator itei;
			for(itei = triggercontext->m_ContextMapI.begin();itei != triggercontext->m_ContextMapI.end(); itei++)
			{
				datalib->setData(context + std::string("/") + itei->first,itei->second);
			}
			std::map<std::string, float>::iterator itef;
			for(itef = triggercontext->m_ContextMapF.begin();itef != triggercontext->m_ContextMapF.end(); itef++)
			{
				datalib->setData(context + std::string("/") + itef->first,itef->second);
			}
			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
		}
	}
	delete triggercontext;
}

void TriggerManager::Trigger(std::string path, std::string triggertype, LuaTempContext * tempcontext)
{

}