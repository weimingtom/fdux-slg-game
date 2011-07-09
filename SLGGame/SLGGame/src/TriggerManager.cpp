#include "TriggerManager.h"

#include "DataLibrary.h"
#include "BattleSquad.h"
#include "LuaSystem.h"
#include "boost/format.hpp"

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
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> triggerlist;
	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
	if(triggerlist.size()>0)
	{
		std::vector<std::string>::iterator ite;
		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
		{
			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
			int active;
			datalib->getData(datapath + std::string("/active"),active);
			if(!active)
				continue;
			std::string type;
			datalib->getData(datapath + std::string("/type"),type);
			if(type != "UnitDead")
				continue;
			std::string context,filename,funcname;
			datalib->getData(datapath + std::string("/file"),filename);
			datalib->getData(datapath + std::string("/func"),funcname);
			datalib->getData(datapath + std::string("/context"),context);
			datalib->setData(context + std::string("/skillcast"),squad->getSquadName());
			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
		}
	}
}

void TriggerManager::turnEnd(int turn, int team)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> triggerlist;
	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
	if(triggerlist.size()>0)
	{
		std::vector<std::string>::iterator ite;
		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
		{
			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
			int active;
			datalib->getData(datapath,active);
			if(!active)
				continue;
			std::string type;
			datalib->getData(datapath + std::string("/type"),type);
			if(type != "TurnEnd")
				continue;
			std::string context,filename,funcname;
			datalib->getData(datapath + std::string("/file"),filename);
			datalib->getData(datapath + std::string("/func"),funcname);
			datalib->getData(datapath + std::string("/context"),context);
			datalib->setData(context + std::string("/trun"),turn);
			datalib->setData(context + std::string("/team"),team);
			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
		}
	}
}

void TriggerManager::finishdeploy()
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> triggerlist;
	triggerlist = datalib->getChildList(std::string("GameData/BattleData/Trigger"));
	if(triggerlist.size()>0)
	{
		std::vector<std::string>::iterator ite;
		for(ite = triggerlist.begin(); ite != triggerlist.end(); ite++)
		{
			std::string datapath = std::string("GameData/BattleData/Trigger/") + (*ite);
			int active;
			datalib->getData(datapath,active);
			if(!active)
				continue;
			std::string type;
			datalib->getData(datapath + std::string("/type"),type);
			if(type != "FinishDeploy")
				continue;
			std::string context,filename,funcname;
			datalib->getData(datapath + std::string("/file"),filename);
			datalib->getData(datapath + std::string("/func"),funcname);
			datalib->getData(datapath + std::string("/context"),context);
			LuaSystem::getSingleton().executeFunction(filename,funcname,context);
		}
	}
}