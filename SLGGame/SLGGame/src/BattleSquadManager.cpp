#include "BattleSquadManager.h"

#include <algorithm>
#include <boost/format.hpp>

#include "MapDataManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"
#include "CommonFunction.h"

#include "LuaSystem.h"
#include "StringTable.h"

#include "AVGSquadManager.h"
#include "Terrain.h"
#include "SquadGrapManager.h"

#include "CutSceneBuilder.h"
#include "FormationCutScence.h"
#include "MoveCutScene.h"
#include "SquadStateCutScene.h"
#include "DefenseCutScene.h"
#include "CombineCutScene.h"
#include "DirectionCutScene.h"
#include "ShowValueCutScene.h"
#include "WeapenCutScene.h"
#include "AnimationCutScene.h"
#include "SquadRecoverCutScene.h"
#include "SquadDeadCutScene.h"
#include "AnimationCutScene.h"
#include "RangedCutScene.h"
#include "MapPUCutScene.h"
#include "CameraContral.h"

#include "MapDataManager.h"

#include "GUIBattle.h"
#include "GUITargetWindow.h"
#include "GUISquadWindows.h"

#include <Shiny.h>

BattleSquadManager::BattleSquadManager()
{

}
BattleSquadManager::~BattleSquadManager()
{

}

void BattleSquadManager::clear()
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		delete ite->second;
	}
	mSquadList.clear();
}


bool  BattleSquadManager::allDeployed()
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getGridX() < 0)
			return false;
	}
	return true;
}

BattleSquad* BattleSquadManager::getBattleSquad(std::string id)
{
	BattleSquadIte ite = mSquadList.find(id);
	if(ite == mSquadList.end())
		return NULL;
	return ite->second;
}

BattleSquad* BattleSquadManager::getBattleSquadAt(int x, int y, int faction, bool visibleonly)
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getGridX() != x)
			continue;
		if(ite->second->getGridY() != y)
			continue;
		if(ite->second->getUnitNum() <= 0)
			continue;
		if(visibleonly)
		{

			switch(faction)
			{
			case 0:
				if(ite->second->getViewbyPlayer())
					return ite->second;
				break;
			case 1:
				if(ite->second->getViewbyEnemy1())
					return ite->second;
				break;
			case 2:
				if(ite->second->getViewbyEnemy2())
					return ite->second;
				break;
			case 3:
				if(ite->second->getViewbyEnemy3())
					return ite->second;
				break;
			}
		}
		else
			return ite->second;
	}
	return NULL;
}

int BattleSquadManager::getTeamSquadLeft(int team)
{
	int num = 0;
	BattleSquadIte ite = mSquadList.begin();
	for(; ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getUnitNum() <= 0)
			continue;
		if(ite->second->getTeam() != team)
			continue;
		num++;
	}
	return num;
}

void BattleSquadManager::dumpSquadData()
{
	BattleSquadIte ite = mSquadList.begin();
	for(; ite!= mSquadList.end(); ite++)
	{
		if(ite->second->getTeam() == 1)
		{
			int unitnum = ite->second->getUnitMaxNum();
			ite->second->setUnitNum(unitnum);
			AVGSquadManager::getSingleton().dumpSquad(ite->second->getSquadId(), ite->second);
		}
	}
}

void BattleSquadManager::turnEnd(int team)
{
	BattleSquadIte ite = mSquadList.begin();
	for(; ite != mSquadList.end(); ite++)
	{
		if(ite->second->getTeam() == team)
		{
			ite->second->turnEnd();
			//重新计算隐藏
			int faction = ite->second->getFaction();
			bool needrecalc = false;
			if(faction != 0)
			{
				needrecalc = ite->second->getViewbyPlayer();
			}
			if(!needrecalc && faction != 1)
			{
				needrecalc = ite->second->getViewbyEnemy1();
			}
			if(!needrecalc && faction != 2)
			{
				needrecalc = ite->second->getViewbyEnemy2();
			}
			if(!needrecalc && faction != 3)
			{
				needrecalc = ite->second->getViewbyEnemy3();
			}
			if(needrecalc)
			{
				bool veiwbyfaction[4] = { false, false, false, false};
				veiwbyfaction[faction] = true;
				int x = ite->second->getGridX();
				int y = ite->second->getGridY();
				BattleSquadIte ite1 = mSquadList.begin();
				for(;ite1 != mSquadList.end(); ite1++)
				{
					if(veiwbyfaction[ite1->second->getFaction()])
						continue;

					int range = GetDistance(x, y, ite1->second->getGridX(), ite1->second->getGridY());
					int ditectrange = (int)ite1->second->getAttr(ATTR_DETECTION,ATTRCALC_FULL) + 2;
					int covert = (int)ite->second->getAttr(ATTR_COVERT,ATTRCALC_FULL);
					if(range <= ditectrange - covert)
					{
						veiwbyfaction[ite1->second->getFaction()] = true;
					}
				}
				if(veiwbyfaction[0] == false)
				{
					ite->second->setViewbyPlayer(0);
					CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(ite->second,SQUAD_STATE_VISIBLE,"none",0));
				}
				if(veiwbyfaction[1] == false)
				{
					ite->second->setViewbyEnemy1(0);
				}
				if(veiwbyfaction[2] == false)
				{
					ite->second->setViewbyEnemy2(0);
				}
				if(veiwbyfaction[3] == false)
				{
					ite->second->setViewbyEnemy3(0);
				}
			}
		}
	}
}

std::map<int, BattleSquadManager::MoveNode> BattleSquadManager::getMoveArea(BattleSquad* squad)
{
	PROFILE_FUNC();
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	std::map<int, MoveNode> movrarea;
	std::vector<int> idlist; 
	MoveNode movenode;
	movenode.x = squad->getGridX();
	movenode.y = squad->getGridY();
	movenode.lastx = squad->getGridX();
	movenode.lasty = squad->getGridY();
	movenode.apleft = squad->getActionPoint();
	movenode.eventflag = 0;
	movrarea.insert(std::make_pair(mapdatamanager->getGridId(movenode.x, movenode.y), movenode));
	idlist.push_back(mapdatamanager->getGridId(movenode.x, movenode.y));
	//寻找可以移动的路径
	unsigned int idnum = 0;
	while(idnum < idlist.size())
	{
		PROFILE_BLOCK(w);
		std::map<int, MoveNode>::iterator ite = movrarea.find(idlist[idnum]);
		int x[4] = {ite->second.x - 1, ite->second.x + 1, ite->second.x, ite->second.x};
		int y[4] = {ite->second.y, ite->second.y, ite->second.y - 1, ite->second.y + 1};
		for(unsigned int n = 0; n < 4; n++)
		{
			float apleft = ite->second.apleft;
			unsigned int eventflag = ite->second.eventflag;
			if(squad->tryMove(ite->second.x, ite->second.y, x[n], y[n], apleft, eventflag))
			{
				std::map<int, MoveNode>::iterator ite1 = movrarea.find(mapdatamanager->getGridId(x[n], y[n]));
				if(ite1 == movrarea.end())
				{
					movenode.x = x[n];
					movenode.y = y[n];
					movenode.lastx = ite->second.x;
					movenode.lasty = ite->second.y;
					movenode.apleft = apleft;
					movenode.eventflag = eventflag;
					movrarea.insert(std::make_pair(mapdatamanager->getGridId(x[n], y[n]), movenode));
					idlist.push_back(mapdatamanager->getGridId(x[n], y[n]));
				}
				else
				{
					if(apleft > ite1->second.apleft)
					{
						ite1->second.lastx = ite->second.x;
						ite1->second.lasty = ite->second.y;
						ite1->second.apleft = apleft;
						ite1->second.eventflag = eventflag;
					}
				}
			}
		}
		idnum++;
	}
	PROFILER_UPDATE();
	return movrarea;
}

std::vector<BattleSquadManager::MoveNode> BattleSquadManager::getMovePath(BattleSquad* squad, int x, int y)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	std::vector<MoveNode> nodelist;
	std::map<int, MoveNode> movrarea = getMoveArea(squad);
	std::map<int, MoveNode>::iterator ite = movrarea.find(mapdatamanager->getGridId(x , y));
	if(ite != movrarea.end())
	{
		while(ite->second.x != squad->getGridX() || ite->second.y != squad->getGridY())
		{
			nodelist.push_back(ite->second);
			ite = movrarea.find(mapdatamanager->getGridId(ite->second.lastx , ite->second.lasty));
		}
	}
	return nodelist;
}

std::map<int, BattleSquadManager::MoveNode> BattleSquadManager::getFullPath(BattleSquad* squad, Crood tatget)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	std::map<int, MoveNode> movrarea;
	std::vector<int> idlist; 
	MoveNode movenode;
	movenode.x = squad->getGridX();
	movenode.y = squad->getGridY();
	movenode.lastx = squad->getGridX();
	movenode.lasty = squad->getGridY();
	movenode.apleft = 0.0f;
	movenode.eventflag = 0;
	movrarea.insert(std::make_pair(mapdatamanager->getGridId(movenode.x, movenode.y), movenode));
	idlist.push_back(mapdatamanager->getGridId(movenode.x, movenode.y));
	//寻找可以移动的路径
	std::map<int, MoveNode>::iterator ite = movrarea.end();
	unsigned int idnum = 0;
	while(idnum < idlist.size())
	{
		ite = movrarea.find(idlist[idnum]);
		int x[4] = {ite->second.x - 1, ite->second.x + 1, ite->second.x, ite->second.x};
		int y[4] = {ite->second.y, ite->second.y, ite->second.y - 1, ite->second.y + 1};
		for(unsigned int n = 0; n < 4; n++)
		{
			if(mapdatamanager->getPassable(x[n], y[n], -1))
			{
				std::map<int, MoveNode>::iterator ite1 = movrarea.find(mapdatamanager->getGridId(x[n], y[n]));
				if(ite1 == movrarea.end())
				{
					movenode.x = x[n];
					movenode.y = y[n];
					movenode.lastx = ite->second.x;
					movenode.lasty = ite->second.y;
					movenode.apleft = ite->second.apleft + 1.0f;
					movrarea.insert(std::make_pair(mapdatamanager->getGridId(x[n], y[n]), movenode));
					idlist.push_back(mapdatamanager->getGridId(x[n], y[n]));
				}
				else
				{
					if(ite->second.apleft < ite1->second.apleft)
					{
						ite1->second.lastx = ite->second.x;
						ite1->second.lasty = ite->second.y;
						ite1->second.apleft = ite->second.apleft + 1.0f;
					}
				}
			}
		}
		idnum++;
	}
	std::map<int, MoveNode> nodelist;
	ite = movrarea.find(mapdatamanager->getGridId(tatget.mX , tatget.mY));
	if(ite == movrarea.end())
	{
		std::map<int, MoveNode>::iterator closeite = movrarea.begin();
		ite = movrarea.begin();
		for( ; closeite != movrarea.end(); closeite++)
		{
			if(GetDistance(closeite->second.x, closeite->second.y, tatget.mX, tatget.mY) 
				< GetDistance(ite->second.x, ite->second.y, tatget.mX, tatget.mY))
			{
				ite = closeite;
			}
		}
	}
	while(ite->second.x != squad->getGridX() || ite->second.y != squad->getGridY())
	{
		nodelist.insert(std::make_pair(ite->first, ite->second));
		ite = movrarea.find(mapdatamanager->getGridId(ite->second.lastx , ite->second.lasty));
	}
	return nodelist;
}

void BattleSquadManager::moveSquad(BattleSquad* squad,std::vector<int> pointlist, unsigned int &stopedpoint, unsigned int &eventflag)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	m_moveSquad = squad;
	m_moveInterrupt = false;
	m_moveList.clear();
	m_startPoint.x = squad->getGridX();
	m_startPoint.y = squad->getGridY();
	for(stopedpoint = 0; stopedpoint * 2 < pointlist.size();stopedpoint++)
	{
		int x = pointlist[stopedpoint*2];
		int y = pointlist[stopedpoint*2 + 1];

		if(!squad->move(x, y, eventflag))
			InterruptMove();

		if(m_moveInterrupt)
			return;

		//计算埋伏
		int faction = squad->getFaction();
		BattleSquad* squadonpoint = getBattleSquadAt(x, y, faction, false);
		if(squadonpoint)
		{
			InterruptMove();
			if(squadonpoint->getViewByFaction(faction) == 0)
			{
				squadonpoint->setViewByFaction(faction, true);
				if(faction == 0)
				{
					CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(squadonpoint,SQUAD_STATE_VISIBLE,"none",1));
				}
			}
			if(squad->getViewByFaction(0))
			{
				CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(squad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadAmbush2"),Ogre::ColourValue(1,1,0,1)));
			}
			squad->setActionPoint(0.0f);
			std::string eid;
			squad->applyEffect("Chaos", eid);
		}

		if(m_moveInterrupt)
		{
			eventflag |= MOVEEVENT_AMBUSH;
			return;
		}

		int lastx = squad->getGridX();
		int lasty = squad->getGridY();
		squad->setGridX(x);
		squad->setGridY(y);
		squad->setDirection(GetDirection(lastx, lasty, x, y));

		m_moveList.push_back(Ogre::Vector2(x, y));

		//触发地图事件
		squad->moveIn(lastx, lasty, x, y);
		std::vector<std::string> inarea;
		std::vector<std::string> outarea;
		mapdata->inOutArea(Crood(lastx, lasty), Crood(x, y), inarea, outarea);
		std::vector<std::string>::iterator areaite = inarea.begin();
		for( ; areaite != inarea.end(); areaite++)
		{
			LuaTempContext * tempcontext = new LuaTempContext();;
			tempcontext->strMap["squadid"] = squad->getSquadId();
			tempcontext->strMap["areaid"] = *areaite;
			mapdata->Trigger("GetInArea", tempcontext);
			delete tempcontext;
		}
		for(areaite = outarea.begin(); areaite != outarea.end(); areaite++)
		{
			LuaTempContext * tempcontext = new LuaTempContext();
			tempcontext->strMap["squadid"] = squad->getSquadId();
			tempcontext->strMap["areaid"] = *areaite;
			mapdata->Trigger("GetOutArea", tempcontext);
			delete tempcontext;
		}
		if(m_moveInterrupt)
		{
			eventflag |= MOVEEVENT_MAPEVENT;
			return;
		}

		BattleSquadIte ite = mSquadList.begin();
		for(;ite != mSquadList.end(); ite++)
		{
			if((ite->second->getFaction()) == faction)
				continue;

			if(!ite->second->getViewByFaction(faction))
			{
				int range = GetDistance(x, y, ite->second->getGridX(), ite->second->getGridY());
				int ditectrange = (int)squad->getAttr(ATTR_DETECTION,ATTRCALC_FULL);
				int covert = (int)ite->second->getAttr(ATTR_COVERT,ATTRCALC_FULL);
				if(range <= ditectrange - covert)
				{
					ite->second->setViewByFaction(faction,true);
					eventflag |= MOVEEVENT_SPOT;
					if(faction == 0)
					{
						InterruptMove();
						CombineCutScene* showValueCutScenes=new CombineCutScene();
						showValueCutScenes->addCutScene(new ShowValueCutScene(squad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadFindEnemy"),Ogre::ColourValue(1,1,0,1)));
						showValueCutScenes->addCutScene(new SquadStateCutScene(ite->second,SQUAD_STATE_VISIBLE,"none",1));
						CutSceneBuilder::getSingleton().addCutScene(showValueCutScenes);
						return;
					}
				}
			}

			if(!squad->getViewByFaction(ite->second->getFaction()))
			{
				int range = GetDistance(x, y, ite->second->getGridX(), ite->second->getGridY());
				int ditectrange = (int)squad->getAttr(ATTR_DETECTION,ATTRCALC_FULL);
				int covert = (int)ite->second->getAttr(ATTR_COVERT,ATTRCALC_FULL);
				if(range <= ditectrange - covert)
				{
					squad->setViewByFaction(ite->second->getFaction(),true);
					squad->setAmbushFaction(ite->second->getFaction(),true);
					if(faction != 0)
					{
						InterruptMove();
						CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(squad, SQUAD_STATE_VISIBLE,"none",1));
						m_moveInterrupt = false;
						m_startPoint.x = squad->getGridX();
						m_startPoint.y = squad->getGridY();
					}
				}
			}

		}

// 		if(eventflag & MOVEEVENT_SPOT)
// 			break;
//		movelist.push_back(Ogre::Vector2(x, y));
	}
	InterruptMove();
// 	if(movelist.size() > 0)
// 	{
// 		MoveCutScene* movecutscne = new MoveCutScene(squad->getSquadId(), movelist, Ogre::Vector2(srcx, srcy));
// 		CutSceneBuilder::getSingleton().addCutScene(movecutscne);
// 	}
}

void BattleSquadManager::forceMoveSquad(BattleSquad* squad, Crood target, unsigned int &eventflag)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	m_moveSquad = squad;
	m_moveInterrupt = false;
	m_moveList.clear();
	m_startPoint.x = squad->getGridX();
	m_startPoint.y = squad->getGridY();

	if(!squad->move(target.mX, target.mY, eventflag, false))
		InterruptMove();

	if(m_moveInterrupt)
		return;

	//计算埋伏
	int faction = squad->getFaction();
	BattleSquad* squadonpoint = getBattleSquadAt(target.mX, target.mY, faction, false);
	if(squadonpoint)
	{
		InterruptMove();
		if(squadonpoint->getViewByFaction(faction) == 0)
		{
			squadonpoint->setViewByFaction(faction, true);
			if(faction == 0)
			{
				CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(squadonpoint,SQUAD_STATE_VISIBLE,"none",1));
			}
		}
		if(squad->getViewByFaction(0))
		{
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(squad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadAmbush2"),Ogre::ColourValue(1,1,0,1)));
		}
		squad->setActionPoint(0.0f);
		std::string eid;
		squad->applyEffect("Chaos", eid);
	}

	if(m_moveInterrupt)
	{
		eventflag |= MOVEEVENT_AMBUSH;
		return;
	}

	int lastx = squad->getGridX();
	int lasty = squad->getGridY();
	squad->setGridX(target.mX);
	squad->setGridY(target.mY);
	squad->setDirection(GetDirection(lastx, lasty, target.mX, target.mY));

	m_moveList.push_back(Ogre::Vector2(target.mX, target.mY));

	//触发地图事件
	squad->moveIn(lastx, lasty, target.mX, target.mY);
	std::vector<std::string> inarea;
	std::vector<std::string> outarea;
	mapdata->inOutArea(Crood(lastx, lasty), target, inarea, outarea);
	std::vector<std::string>::iterator areaite = inarea.begin();
	for( ; areaite != inarea.end(); areaite++)
	{
		LuaTempContext * tempcontext = new LuaTempContext();;
		tempcontext->strMap["squadid"] = squad->getSquadId();
		tempcontext->strMap["areaid"] = *areaite;
		mapdata->Trigger("GetInArea", tempcontext);
		delete tempcontext;
	}
	for(areaite = outarea.begin(); areaite != outarea.end(); areaite++)
	{
		LuaTempContext * tempcontext = new LuaTempContext();
		tempcontext->strMap["squadid"] = squad->getSquadId();
		tempcontext->strMap["areaid"] = *areaite;
		mapdata->Trigger("GetOutArea", tempcontext);
		delete tempcontext;
	}
	if(m_moveInterrupt)
	{
		eventflag |= MOVEEVENT_MAPEVENT;
		return;
	}

	BattleSquadIte ite = mSquadList.begin();
	for(;ite != mSquadList.end(); ite++)
	{
		if((ite->second->getFaction()) == faction)
			continue;

		if(!ite->second->getViewByFaction(faction))
		{
			int range = GetDistance(target.mX, target.mY, ite->second->getGridX(), ite->second->getGridY());
			int ditectrange = (int)squad->getAttr(ATTR_DETECTION,ATTRCALC_FULL);
			int covert = (int)ite->second->getAttr(ATTR_COVERT,ATTRCALC_FULL);
			if(range <= ditectrange - covert)
			{
				ite->second->setViewByFaction(faction,true);
				eventflag |= MOVEEVENT_SPOT;
				if(faction == 0)
				{
					InterruptMove();
					CombineCutScene* showValueCutScenes=new CombineCutScene();
					showValueCutScenes->addCutScene(new ShowValueCutScene(squad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadFindEnemy"),Ogre::ColourValue(1,1,0,1)));
					showValueCutScenes->addCutScene(new SquadStateCutScene(ite->second,SQUAD_STATE_VISIBLE,"none",1));
					CutSceneBuilder::getSingleton().addCutScene(showValueCutScenes);
					return;
				}
			}
		}

		if(!squad->getViewByFaction(ite->second->getFaction()))
		{
			int range = GetDistance(target.mX, target.mY, ite->second->getGridX(), ite->second->getGridY());
			int ditectrange = (int)squad->getAttr(ATTR_DETECTION,ATTRCALC_FULL);
			int covert = (int)ite->second->getAttr(ATTR_COVERT,ATTRCALC_FULL);
			if(range <= ditectrange - covert)
			{
				squad->setViewByFaction(ite->second->getFaction(),true);
				squad->setAmbushFaction(ite->second->getFaction(),true);
				if(faction != 0)
				{
					InterruptMove();
					CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(squad, SQUAD_STATE_VISIBLE,"none",1));
					m_moveInterrupt = false;
					m_startPoint.x = squad->getGridX();
					m_startPoint.y = squad->getGridY();
				}
			}
		}
	}

	InterruptMove();
}

void BattleSquadManager::InterruptMove()
{
	if(m_moveList.size() > 0)
	{
		MoveCutScene* movecutscne = new MoveCutScene(m_moveSquad->getSquadId(), m_moveList, m_startPoint);
		CutSceneBuilder::getSingleton().addCutScene(movecutscne);
		m_moveList.clear();
	}
	m_moveInterrupt = true;
}

void BattleSquadManager::changeFormation(BattleSquad* squad, int formation, bool costap)
{
	if(squad->changeFormation(formation, costap))
	{
		FormationCutScene* formcutscene = new FormationCutScene(squad->getSquadId(), formation);
		CutSceneBuilder::getSingleton().addCutScene(formcutscene);
	}
}

// bool BattleSquadManager::useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid)
// {
// 	if(attacksquad == NULL || targetsquad == NULL )
// 		return false;
// 	DataLibrary* datalib = DataLibrary::getSingletonPtr();
// 	return true;
// }
// 
// bool BattleSquadManager::useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid)
// {
// 	if(attacksquad == NULL)
// 		return false;
// 	DataLibrary* datalib = DataLibrary::getSingletonPtr();
// 	return true;
// }

std::vector<BattleSquadManager::SkillNode> BattleSquadManager::getSkillArea(BattleSquad* squad, std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	LuaSystem* luasystem = LuaSystem::getSingletonPtr();

	std::vector<SkillNode> skillarea;
	
	SkillNode skillnode;

	int skilltype;
	bool re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/Type")%skillid),skilltype);
	int minrange;
	re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/MinRange")%skillid),minrange);
	int maxrange;
	re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/MaxRange")%skillid),maxrange);
	std::string script;
	re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/Script")%skillid),script);
	std::string contextpath = str(boost::format("%1%/Skill/%2%/ScriptContext")%squad->getPath()%skillid);
	switch(skilltype)
	{
	case SKILLTARGETTYPE_TARGETSQUAD:
	case SKILLTARGETTYPE_RANGED:
		{
			if(skilltype == SKILLTARGETTYPE_RANGED)
			{
				int weaponminrange = 1, weaponmaxrange = 3;
				std::string sweapon = squad->getSweaponId();
				datalib->getData(str(boost::format("StaticData/SweaponData/%1%/MinRange")%sweapon),weaponminrange);
				datalib->getData(str(boost::format("StaticData/SweaponData/%1%/MaxRange")%sweapon),weaponmaxrange);
				minrange = weaponminrange - minrange;
				minrange = (minrange < 0)?0:minrange;
				maxrange = weaponmaxrange + maxrange;
			}
			int minx,miny,maxx, maxy;
			minx = squad->getGridX() - maxrange;
			minx = (minx < 0)?0:minx;
			miny = squad->getGridY() - maxrange;
			miny = (miny < 0)?0:miny;
			maxx = squad->getGridX() + maxrange;
			maxx = (maxx > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxx;
			maxy = squad->getGridY() + maxrange;
			maxy = (maxy > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxy;
			for(int x = minx; x <= maxx; x++)
			{
				for(int y = miny; y <= maxy; y++)
				{
					int range = abs(x - squad->getGridX()) + abs(y - squad->getGridY());
					if(range <= maxrange && range >= minrange)
					{
						//判断区域是否符合
						bool validarea = false;
						LuaTempContext* luatempcontext = new LuaTempContext;
						luatempcontext->strMap["squadid"] = squad->getSquadId();
						luatempcontext->intMap["targetx"] = x;
						luatempcontext->intMap["targety"] = y;
						luatempcontext->intMap["validarea"] = 0;
						luasystem->executeFunction(script, "validarea", contextpath, luatempcontext);
						if(luatempcontext->intMap["validarea"] == 1)
							validarea = true;
						if(validarea)
						{
							skillnode.x = x;
							skillnode.y = y;
							skillnode.validTarget = false;

							//判断目标是否符合
							BattleSquad* targetsquad = getBattleSquadAt(x, y, squad->getFaction(), true);
							if(targetsquad)
							{
								luatempcontext->strMap["targetsquadid"] = targetsquad->getSquadId();
								luatempcontext->intMap["validtarget"] = 0;
								luasystem->executeFunction(script, "validtarget", contextpath, luatempcontext);
								if(luatempcontext->intMap["validtarget"] == 1)
								{
									skillnode.validTarget = true;
									skillnode.direction = GetDirection(x, y, squad->getGridX(), squad->getGridY());
								}
							}
							skillarea.push_back(skillnode);
						}
						delete luatempcontext;
					}
				}
			}
	
		}
		break;
	case SKILLTARGETTYPE_MELEE:
		{
			float apcost = squad->getSkillApCost(skillid);
			std::map<int, int> meleesquadmap;
			std::map<int, MoveNode> movenodes = getMoveArea(squad);
			std::map<int, MoveNode>::iterator ite = movenodes.begin();
			for(; ite != movenodes.end(); ite++)
			{
				skillnode.x = ite->second.x;
				skillnode.y = ite->second.y;
				skillnode.validTarget = false;
				skillarea.push_back(skillnode);
				if(ite->second.apleft >= apcost)
				{
					//寻找可攻击的目标
					int x[4] = {ite->second.x - 1, ite->second.x + 1, ite->second.x, ite->second.x};
					int y[4] = {ite->second.y, ite->second.y, ite->second.y - 1, ite->second.y + 1};
					for(unsigned int n = 0 ; n < 4; n++)
					{
						BattleSquad* targetsquad = getBattleSquadAt(x[n], y[n], squad->getFaction(), true);
						if(targetsquad)
						{
							LuaTempContext* luatempcontext = new LuaTempContext;
							luatempcontext->strMap["squadid"] = squad->getSquadId();
							luatempcontext->intMap["x"] = ite->second.x;
							luatempcontext->intMap["y"] = ite->second.y;
							luatempcontext->strMap["targetsquadid"] = targetsquad->getSquadId();
							luatempcontext->intMap["targetx"] = x[n];
							luatempcontext->intMap["targety"] = y[n];
							luatempcontext->intMap["validtarget"] = 0;
							luasystem->executeFunction(script, "validtarget", contextpath, luatempcontext);
							if(luatempcontext->intMap["validtarget"] == 1)
							{
								std::map<int, int>::iterator ite1 = meleesquadmap.find(mapdatamanager->getGridId(x[n], y[n]));
								if(ite1 == meleesquadmap.end())
								{
									meleesquadmap.insert(std::make_pair(mapdatamanager->getGridId(x[n], y[n]), 
																		mapdatamanager->getGridId(ite->second.x, ite->second.y)));
								}
								else if(movenodes[ite1->second].apleft <= ite->second.apleft)
								{
									ite1->second = mapdatamanager->getGridId(ite->second.x, ite->second.y);
								}
							}
						}
					}
				}
			}
			std::map<int, int>::iterator ite1 = meleesquadmap.begin();
			for(; ite1 != meleesquadmap.end(); ite1++)
			{
				mapdatamanager->getCrood(ite1->first, skillnode.x, skillnode.y);
				skillnode.validTarget = true;
				int x, y;
				mapdatamanager->getCrood(ite1->second, x, y);
				skillnode.direction = GetDirection(skillnode.x, skillnode.y, x, y);
				skillarea.push_back(skillnode);
			}
		}
		break;
	case SKILLTARGETTYPE_TARGETAREA:
	case SKILLTARGETTYPE_TARGETLINE:
		{
			int minx,miny,maxx, maxy;
			minx = squad->getGridX() - maxrange;
			minx = (minx < 0)?0:minx;
			miny = squad->getGridY() - maxrange;
			miny = (miny < 0)?0:miny;
			maxx = squad->getGridX() + maxrange;
			maxx = (maxx > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxx;
			maxy = squad->getGridY() + maxrange;
			maxy = (maxy > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxy;
			for(int x = minx; x <= maxx; x++)
			{
				for(int y = miny; y <= maxy; y++)
				{
					int range = abs(x - squad->getGridX()) + abs(y - squad->getGridY());
					if(range <= maxrange && range >= minrange)
					{
						//判断区域是否符合
						bool validarea = false;
						LuaTempContext* luatempcontext = new LuaTempContext;
						luatempcontext->strMap["squadid"] = squad->getSquadId();
						luatempcontext->intMap["targetx"] = x;
						luatempcontext->intMap["targety"] = y;
						luatempcontext->intMap["validarea"] = 0;
						luasystem->executeFunction(script, "validarea", contextpath, luatempcontext);
						if(luatempcontext->intMap["validarea"] == 1)
							validarea = true;
						if(validarea)
						{
							skillnode.x = x;
							skillnode.y = y;
							skillnode.validTarget = true;

							skillarea.push_back(skillnode);
						}
						delete luatempcontext;
					}
				}
			}
		}
		break;
	}
	
	return skillarea;
}

std::vector<BattleSquadManager::SkillNode> BattleSquadManager::getSkillTargetArea(BattleSquad* squad, std::string skillid, int x, int y)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<SkillNode> skillarea;

	SkillNode skillnode;

	int skilltype;
	bool re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/Type")%skillid),skilltype);
	switch(skilltype)
	{
	case SKILLTARGETTYPE_TARGETSQUAD:
	case SKILLTARGETTYPE_RANGED:
		{
			skillnode.x = x;
			skillnode.y = y;
			skillnode.validTarget = true;
			skillarea.push_back(skillnode);
		}
		break;
	case SKILLTARGETTYPE_MELEE:
		{
			std::vector<SkillNode> skillnodelist = getSkillArea(squad, skillid);
			std::vector<SkillNode>::iterator ite = skillnodelist.begin();
			for( ; ite!= skillnodelist.end(); ite++)
			{
				if(x == (*ite).x && y == (*ite).y)
				{
					int movex = x, movey = y;
					if((*ite).validTarget)
					{
						skillnode.x = x;
						skillnode.y = y;
						skillnode.validTarget = true;
						skillnode.direction = (*ite).direction;
						skillarea.push_back(skillnode);
						switch((*ite).direction)
						{
						case North:
							movey -= 1;
							break;
						case South:
							movey += 1;
							break;
						case East:
							movex += 1;
							break;
						case West:
							movex -= 1;
							break;
						}
					}
					std::vector<MoveNode> movepath = getMovePath(squad, movex, movey);
					std::vector<MoveNode>::iterator ite1 =  movepath.begin();
					for(; ite1 != movepath.end(); ite1++)
					{
						skillnode.x = (*ite1).x;
						skillnode.y = (*ite1).y;
						skillnode.validTarget = false;
						skillarea.push_back(skillnode);
					}
				}
			}
		}
		break;
	case SKILLTARGETTYPE_TARGETAREA:
	case SKILLTARGETTYPE_TARGETLINE:
		{
			MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
			LuaSystem* luasystem = LuaSystem::getSingletonPtr();

			int area;
			bool re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/Area")%skillid),area);

			int minx,miny,maxx, maxy;
			minx = x - area;
			minx = (minx < 0)?0:minx;
			miny = y - area;
			miny = (miny < 0)?0:miny;
			maxx = x + area;
			maxx = (maxx > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxx;
			maxy = y + area;
			maxy = (maxy > mapdatamanager->getMapSize() - 1)?mapdatamanager->getMapSize() - 1:maxy;
			for(int tgx = minx; tgx <= maxx; tgx++)
			{
				for(int tgy = miny; tgy <= maxy; tgy++)
				{
					int range = abs(tgx - x) + abs(tgy - y);
					if(range <= area)
					{
						//判断区域是否符合
						std::string script;
						datalib->getData(str(boost::format("StaticData/SkillData/%1%/Script")%skillid),script);
						std::string contextpath = str(boost::format("%1%/Skill/%2%/ScriptContext")%squad->getPath()%skillid);
						bool validaffectarea = false;
						LuaTempContext* luatempcontext = new LuaTempContext;
						luatempcontext->strMap["squadid"] = squad->getSquadId();
						luatempcontext->intMap["centerx"] = x;
						luatempcontext->intMap["centery"] = y;
						luatempcontext->intMap["targetx"] = tgx;
						luatempcontext->intMap["targety"] = tgy;
						luatempcontext->intMap["validaffectarea"] = 0;
						luasystem->executeFunction(script, "validaffectarea", contextpath, luatempcontext);
						if(luatempcontext->intMap["validaffectarea"] == 1)
							validaffectarea = true;
						if(validaffectarea)
						{
							skillnode.x = tgx;
							skillnode.y = tgy;
							skillnode.validTarget = true;

							skillarea.push_back(skillnode);
						}
						delete luatempcontext;
					}
				}
			}
		}
		break;
	}

	return skillarea;
}

void BattleSquadManager::useSkill(BattleSquad* squad, std::string skillid, int x, int y, unsigned int &eventflag)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int skilltype;
	bool re = datalib->getData(str(boost::format("StaticData/SkillData/%1%/Type")%skillid),skilltype);
	switch(skilltype)
	{
	case SKILLTARGETTYPE_TARGETSQUAD:
	case SKILLTARGETTYPE_RANGED:
		{
			BattleSquad* targetsquad = getBattleSquadAt(x, y, squad->getFaction(), true);
			if(targetsquad)
				squad->useSkillOn(targetsquad, skillid);
		}
		break;
	case SKILLTARGETTYPE_TARGETAREA:
		{
			squad->useSkillAt(x, y, skillid);
		}
		break;
	case SKILLTARGETTYPE_MELEE:
		{
			std::vector<SkillNode> skillnodelist = getSkillArea(squad, skillid);
			std::vector<SkillNode>::iterator ite = skillnodelist.begin();
			for( ; ite!= skillnodelist.end(); ite++)
			{
				if(x == (*ite).x && y == (*ite).y)
				{
					int movex = x, movey = y;
					if((*ite).validTarget)
					{
						switch((*ite).direction)
						{
						case North:
							movey -= 1;
							break;
						case South:
							movey += 1;
							break;
						case East:
							movex += 1;
							break;
						case West:
							movex -= 1;
							break;
						}
					}
					std::vector<int> pathlist;
					std::vector<MoveNode> movepath = getMovePath(squad, movex, movey);
					std::vector<MoveNode>::reverse_iterator rite;
					for(rite = movepath.rbegin(); rite != movepath.rend(); rite++)
					{
						pathlist.push_back((*rite).x);
						pathlist.push_back((*rite).y);
					}
					unsigned int stoppoint;
					moveSquad(squad, pathlist, stoppoint, eventflag);
					if(!(eventflag & (MOVEEVENT_WRONG | MOVEEVENT_AMBUSH | MOVEEVENT_SPOT)))
					{
						BattleSquad* targetsquad = getBattleSquadAt(x, y, squad->getFaction(), true);
						if(targetsquad)
						{
							bool charge = false;
							if(eventflag & MOVEEVENT_CHARGE)
							{
								int chagedir = GetChargeDir(eventflag);
								int targetdir = GetDirection(squad->getGridX(), squad->getGridY(),
									targetsquad->getGridX(), targetsquad->getGridY());
								if(targetdir == chagedir)
								{
									squad->onCharge();
									charge = true;	
								}
							}
							squad->useSkillOn(targetsquad, skillid);
							if(charge)
							{
								squad->afterCharge();
							}
						}
					}
				}
			}
		}
		break;
	}
}

bool BattleSquadManager::dealMeleeDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	CutSceneBuilder* cutscenebuilder = CutSceneBuilder::getSingletonPtr();

	if(attacksquad->getTeam()!=1)
	{
		float wx,wy;
		Terrain::getSingletonPtr()->getWorldCoords(attacksquad->getGridX(),attacksquad->getGridY(),wx,wy);
		CameraContral::getSingletonPtr()->moveCameraTo(wx,wy);
	}

	//计算突袭
	int deffaction = defenesquad->getFaction();
	if(attacksquad->getViewByFaction(deffaction) == false)
	{
		attacksquad->setViewByFaction(deffaction, true);
		attacksquad->setAmbushFaction(deffaction, true);
		if(deffaction == 0)
		{
			cutscenebuilder->addCutScene(new SquadStateCutScene(attacksquad,SQUAD_STATE_VISIBLE,"none",1));
		}
	}
	if(attacksquad->getAmbushFaction(deffaction) == true)
	{
		if(defenesquad->getViewByFaction(0))
		{
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadAmbush1"),Ogre::ColourValue(1,1,0,1)));
		}
		std::string eid;
		defenesquad->applyEffect("Chaos", eid);
		attacksquad->setAmbushFaction(deffaction, false);
	}

	Direction d,dd;
	int defenderx, defendery, attackerx,attackery;
	attackerx = attacksquad->getGridX();
	attackery = attacksquad->getGridY();
	defenderx = defenesquad->getGridX();
	defendery = defenesquad->getGridY();

	d = GetDirection(attackerx,attackery,defenderx,defendery);
	if(attacksquad->getDirection() != d)
	{
		attacksquad->setDirection(d);
		cutscenebuilder->addCutScene(new DirectionCutScene(attacksquad->getSquadId(), d));
	}

	cutscenebuilder->addCutScene(new WeapenCutScene(attacksquad->getSquadId(),WeapenCutScene::MainWepon));
	cutscenebuilder->addCutScene(new WeapenCutScene(defenesquad->getSquadId(),WeapenCutScene::MainWepon));

	dd = defenesquad->getDirection();
	Direction temp[4] = {South,North,East,West};
	cutscenebuilder->addCutScene(new DirectionCutScene(defenesquad->getSquadId(),temp[d]));

	float atkint = attacksquad->getAttr(ATTR_INITIATIVE, ATTRCALC_FULL);
	float defint = defenesquad->getAttr(ATTR_INITIATIVE, ATTRCALC_FULL);
	BattleSquad* squad = NULL;
	if(atkint>=defint)
		squad = attacksquad;
	else
		squad = defenesquad;

	CombineCutScene* showValueCutScenes=new CombineCutScene();
	for(int n = 0; n < 2; n++)
	{
		//攻击动作
		if(squad->getType() == SQUAD_NORMAL)
			cutscenebuilder->addCutScene(new AnimationCutScene(squad->getSquadId(),UNITTYPE_ALL,"Attack","0","none",false,true));
		else
			cutscenebuilder->addCutScene(new AnimationCutScene(squad->getSquadId(),UNITTYPE_SOLIDER,"Attack","0","none",false,true));
		AttackInfo atkinfo;
		if(squad == attacksquad)
		{
			squad->onMeleeAttack(defenesquad, false);
			atkinfo = squad->getAttackRolls(false,false,d);
			if(attacksquad->getFormation() == Line)
			{
				switch(defenesquad->getFormation())
				{
				case Line:
					if(GetSide(dd,temp[d]) != 0)
					{
						std::string eid;
						defenesquad->applyEffect("Waver", eid);
						//if(GetSide(dd,temp[d]) == 2)
						//{
						//	defenesquad->applyEffect("Waver", eid);
						//}
					}
					break;
				case Loose:
					{
						std::string eid;
						defenesquad->applyEffect("Waver", eid);
					}
					break;
				}
			}
			squad = defenesquad;
		}
		else
		{
			squad->onMeleeAttack(attacksquad, true);
			atkinfo = squad->getAttackRolls(false,true,temp[d]);
			squad = attacksquad;
		}
		if(atkinfo.AtkTime > 0)
		{
			int squadugb = squad->getUnitGrapNum();
			int squadRealNumB=squad->getUnitNum();
			if(squad == attacksquad)
			{
				squad->applyAttackRolls(false, d, atkinfo);
				defenesquad->afterMeleeAttack(squad, true);
			}
			else
			{
				squad->applyAttackRolls(false, temp[d], atkinfo);
				attacksquad->afterMeleeAttack(squad, false);
			}
			int squaduga = squad->getUnitGrapNum();
			int squadRealNumA=squad->getUnitNum();
			if(squaduga <= squadugb)
			{
				//setCutScene(new SquadDeadCutScene(squad->getGrapId(), squadugb - squaduga));
				if(squad == attacksquad)
					showValueCutScenes->addCutScene(new DefenseCutScene(defenesquad->getSquadId(),squad->getSquadId(), squadugb - squaduga));
				else
					showValueCutScenes->addCutScene(new DefenseCutScene(attacksquad->getSquadId(),squad->getSquadId(), squadugb - squaduga));
			}
			if(squad->getUnitNum() == 0)
			{
				cutscenebuilder->addCutScene(new SquadStateCutScene(squad,SQUAD_STATE_VISIBLE,"none",0));
				showValueCutScenes->addCutScene(new ShowValueCutScene(squad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadDead"),Ogre::ColourValue::Red));
			}
			else
			{
				showValueCutScenes->addCutScene(new ShowValueCutScene(squad->getSquadId(),str(boost::format(StringTable::getSingletonPtr()->getString("BattleInfo"))%(squadRealNumB-squadRealNumA)),Ogre::ColourValue::Red));
			}
		}
	}

	cutscenebuilder->addCutScene(showValueCutScenes);

	GUIBattle* guibattle=static_cast<GUIBattle *>(GUISystem::getSingleton().createScene(BattleScene));
	GUITargetWindows* targetGUI=(GUITargetWindows*)guibattle->getSubWindow("TargetWindow");
	targetGUI->updateSquad();
	GUISquadWindows* squadGUI=(GUISquadWindows*)guibattle->getSubWindow("SquadWindow");
	squadGUI->updateSquad();

	if(defenesquad->getUnitNum() > 0)
		cutscenebuilder->addCutScene(new DirectionCutScene(defenesquad->getSquadId(),dd));

	return true;
}

bool BattleSquadManager::dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk, int randomness)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	CutSceneBuilder* cutscenebuilder = CutSceneBuilder::getSingletonPtr();

	if(attacksquad->getTeam()!=1)
	{
		float wx,wy;
		Terrain::getSingletonPtr()->getWorldCoords(attacksquad->getGridX(),attacksquad->getGridY(),wx,wy);
		CameraContral::getSingletonPtr()->moveCameraTo(wx,wy);
	}

	int deffaction = defenesquad->getFaction();
	if(attacksquad->getViewByFaction(deffaction) == false)
	{
		attacksquad->setViewByFaction(deffaction, true);
		attacksquad->setAmbushFaction(deffaction, true);
		if(deffaction == 0)
		{
			cutscenebuilder->addCutScene(new SquadStateCutScene(attacksquad,SQUAD_STATE_VISIBLE,"none",1));
		}
	}
	if(attacksquad->getAmbushFaction(deffaction) == true)
	{
		if(defenesquad->getViewByFaction(0))
		{
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadAmbush1"),Ogre::ColourValue(1,1,0,1)));
		}
		std::string eid;
		defenesquad->applyEffect("Chaos", eid);
		attacksquad->setAmbushFaction(deffaction, false);
	}

	defenesquad->onUnderMagicAttack(attacksquad);

	AttackInfo atkinfo;
	atkinfo.Atk = atk;
	atkinfo.AtkTime = attacktime;
	atkinfo.Randomness = randomness;
	int squadugb = defenesquad->getUnitGrapNum();
	int squadRealNumB = defenesquad->getUnitNum();
	defenesquad->applyAttackRolls(true, defenesquad->getDirection(), atkinfo);
	int squaduga = defenesquad->getUnitGrapNum();
	int squadRealNumA = defenesquad->getUnitNum();

	if(squadugb - squaduga  > 0 )
	{
		CombineCutScene* showValueCutScenes=new CombineCutScene();
		showValueCutScenes->addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),str(boost::format(StringTable::getSingletonPtr()->getString("BattleInfo"))%(squadRealNumB-squadRealNumA)),Ogre::ColourValue::Red));
		showValueCutScenes->addCutScene(new SquadDeadCutScene(defenesquad->getSquadId(), squadugb - squaduga));
		cutscenebuilder->addCutScene(showValueCutScenes);
	}
	else
	{
		cutscenebuilder->addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),str(boost::format(StringTable::getSingletonPtr()->getString("BattleInfo"))%(squadRealNumB-squadRealNumA)),Ogre::ColourValue::Red));
	}

	if(defenesquad->getUnitNum() == 0)
	{
		cutscenebuilder->addCutScene(new SquadStateCutScene(defenesquad, SQUAD_STATE_VISIBLE, "none", 0));
	}
	else if(defenesquad->getFormation() == Circular)
	{
		std::string eid;
		defenesquad->applyEffect("Waver", eid);
	}
	defenesquad->afterUnderMagicAttack(attacksquad);
	return true;
}

bool BattleSquadManager::dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	CutSceneBuilder* cutscenebuilder = CutSceneBuilder::getSingletonPtr();

	if(attacksquad->getTeam()!=1)
	{
		float wx,wy;
		Terrain::getSingletonPtr()->getWorldCoords(attacksquad->getGridX(),attacksquad->getGridY(),wx,wy);
		CameraContral::getSingletonPtr()->moveCameraTo(wx,wy);
	}

	int deffaction = defenesquad->getFaction();
	if(attacksquad->getViewByFaction(deffaction) == false)
	{
		attacksquad->setViewByFaction(deffaction, true);
		attacksquad->setAmbushFaction(deffaction, true);
		if(deffaction == 0)
		{
			cutscenebuilder->addCutScene(new SquadStateCutScene(attacksquad,SQUAD_STATE_VISIBLE,"none",1));
		}
	}
	if(attacksquad->getAmbushFaction(deffaction) == true)
	{
		if(defenesquad->getViewByFaction(0))
		{
			CutSceneBuilder::getSingleton().addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),StringTable::getSingletonPtr()->getString("SquadAmbush1"),Ogre::ColourValue(1,1,0,1)));
		}
		std::string eid;
		defenesquad->applyEffect("Chaos", eid);
		attacksquad->setAmbushFaction(deffaction, false);
	}

	attacksquad->onRangedAttack(defenesquad);
	defenesquad->onUnderRangedAttack(attacksquad);

	int x = defenesquad->getGridX();
	int y = defenesquad->getGridY();
	rangedCutScene(attacksquad, x, y, UNITTYPE_ALL, "none","Attack","1",0,"none","none","none");

	AttackInfo atkinfo;
	atkinfo = attacksquad->getAttackRolls(true, false, attacksquad->getDirection());

	int squadugb = defenesquad->getUnitGrapNum();
	int squadRealNumB = defenesquad->getUnitNum();
	defenesquad->applyAttackRolls(true, defenesquad->getDirection(), atkinfo);
	int squaduga = defenesquad->getUnitGrapNum();
	int squadRealNumA = defenesquad->getUnitNum();

	if(squadugb - squaduga  > 0 )
	{
		CombineCutScene* showValueCutScenes=new CombineCutScene();
		showValueCutScenes->addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),str(boost::format(StringTable::getSingletonPtr()->getString("BattleInfo"))%(squadRealNumB-squadRealNumA)),Ogre::ColourValue::Red));
		showValueCutScenes->addCutScene(new SquadDeadCutScene(defenesquad->getSquadId(), squadugb - squaduga));
		cutscenebuilder->addCutScene(showValueCutScenes);
	}
	else
	{
		cutscenebuilder->addCutScene(new ShowValueCutScene(defenesquad->getSquadId(),str(boost::format(StringTable::getSingletonPtr()->getString("BattleInfo"))%(squadRealNumB-squadRealNumA)),Ogre::ColourValue::Red));
	}

	attacksquad->afterRangedAttack(defenesquad);
	if(defenesquad->getUnitNum() == 0)
	{
		cutscenebuilder->addCutScene(new SquadStateCutScene(defenesquad, SQUAD_STATE_VISIBLE, "none", 0));
	}
	else if(defenesquad->getFormation() == Circular)
	{
		std::string eid;
		defenesquad->applyEffect("Waver", eid);
	}
	defenesquad->afterUnderRangedAttack(attacksquad);

	return true;
}

void BattleSquadManager::setUnitNum(BattleSquad* squad, int unitnum)
{
	if(squad->getUnitMaxNum() < unitnum)
		return;
	CutSceneBuilder* cutscenebuilder = CutSceneBuilder::getSingletonPtr();
	int squadugb = squad->getUnitGrapNum();
	squad->setUnitNum(unitnum);
	int squaduga = squad->getUnitGrapNum();
	if(squaduga > squadugb)
	{
		cutscenebuilder->addCutScene(new SquadRecoverCutScene(squad->getSquadId(), squaduga - squadugb));
	}
	else if(squaduga < squadugb)
	{
		cutscenebuilder->addCutScene(new SquadDeadCutScene(squad->getSquadId(), squadugb - squaduga));
	}

	if(squad->getUnitNum() == 0)
	{
		cutscenebuilder->addCutScene(new SquadStateCutScene(squad, SQUAD_STATE_VISIBLE, "none", 0));
	}
}

void BattleSquadManager::setDirection(BattleSquad* squad, int direction)
{
	if(squad->getDirection() != direction)
	{
		squad->setDirection(direction);
		CutSceneBuilder::getSingleton().addCutScene(new DirectionCutScene(squad->getSquadId(),direction));
	}
}

void BattleSquadManager::rangedCutScene(BattleSquad* attacksquad, int x, int y, UnitType castunit , std::string castparticle, std::string castaction, std::string castsound, int missiletype, std::string missileres, std::string hitparticle,std::string hitsound)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	CutSceneBuilder* cutscenebuilder = CutSceneBuilder::getSingletonPtr();
	//设置小队朝向
	Direction d;
	int casterx,castery;
	casterx = attacksquad->getGridX();
	castery = attacksquad->getGridY();
	if(casterx != x || castery != y)
	{
		d = GetDirection(casterx,castery,x,y);
		setDirection(attacksquad, d);
	}
	else
		return;

	cutscenebuilder->addCutScene(new WeapenCutScene(attacksquad->getSquadId(),WeapenCutScene::SceWepon));

	cutscenebuilder->addCutScene(new AnimationCutScene(attacksquad->getSquadId(),castunit,castaction,castsound,castparticle,false, true));

	CombineCutScene* ccs = new CombineCutScene;
	float xx,yy;
	Terrain::getSingleton().getWorldCoords(x,y,xx,yy);
	SquadGraphics* squadgrap = SquadGrapManager::getSingleton().getSquad(attacksquad->getSquadId());
	if(castunit & UNITTYPE_LEADER)
	{
		Ogre::Vector3 startpoint = squadgrap->getLeaderPosition();
		startpoint = startpoint + Ogre::Vector3(0.0f,6.0f,0.0f);
		Ogre::Vector3 endpoint = Ogre::Vector3(xx - TILESIZE/2.0f + (rand()%int(TILESIZE)),0.0f,yy - TILESIZE/2.0f + (rand()%int(TILESIZE)));
		RangedCutScene* rangedcutscene = new RangedCutScene(startpoint,endpoint,missiletype,missileres);
		ccs->addCutScene(rangedcutscene);
		if(hitparticle != "none")
			rangedcutscene->setNextScene(new MapPUCutScene(endpoint,1.0f,hitparticle,hitsound));
	}
	if(castunit & UNITTYPE_SOLIDER)
	{
		std::vector<Ogre::Vector3> posvec;
		posvec = squadgrap->getSoiderPosition();
		std::vector<Ogre::Vector3>::iterator ite;
		for(ite = posvec.begin(); ite != posvec.end(); ite++)
		{
			Ogre::Vector3 startpoint = (*ite);
			startpoint = startpoint + Ogre::Vector3(0.0f,6.0f,0.0f);
			Ogre::Vector3 endpoint = Ogre::Vector3(xx - TILESIZE/2.0f + (rand()%int(TILESIZE)),0.0f,yy - TILESIZE/2.0f + (rand()%int(TILESIZE)));
			RangedCutScene* rangedcutscene = new RangedCutScene(startpoint,endpoint,missiletype,missileres);
			ccs->addCutScene(rangedcutscene);
			if(hitparticle != "none")
				rangedcutscene->setNextScene(new MapPUCutScene(endpoint,1.0f,hitparticle,hitsound));
		}
	}
	cutscenebuilder->addCutScene(ccs);
}

bool BattleSquadManager::createStorySquad(std::string squadid, std::string suqadtypeid, int x, int y,bool NoCreate)
{
	if(getBattleSquadAt(x, y, 0, false) != NULL)
		return false;
	if(!NoCreate)
		AVGSquadManager::getSingleton().addNewSquad(squadid, suqadtypeid);

	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();

	std::string path = "GameData/BattleData/SquadList";
	BattleSquad* battlesquad = new BattleSquad(str(boost::format("%1%/%2%")%path%squadid));
	mSquadList.insert(std::make_pair(battlesquad->getSquadId(),battlesquad));
	if(!battlesquad->init(str(boost::format("GameData/StoryData/SquadData/%1%")%squadid), 1))
	{
		BattleSquadIte ite = mSquadList.find(battlesquad->getSquadId());
		delete battlesquad;
		mSquadList.erase(ite);
		return false;
	}
	battlesquad->setGridX(x);
	battlesquad->setGridY(y);
	suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
										battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
	SquadGraphics* grap = suqadgrapmanager->getSquad(battlesquad->getSquadId());
	grap->setVisible(false);
	CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(battlesquad, SQUAD_STATE_VISIBLE, "none",1));
	return true;
}
bool BattleSquadManager::createNormalSquad(std::string squadid, std::string suqadtypeid, int x, int y, int team, int unitnum)
{
	if(getBattleSquadAt(x, y, 0, false) != NULL)
		return false;
	SquadGrapManager* suqadgrapmanager = SquadGrapManager::getSingletonPtr();
	std::string path = "GameData/BattleData/SquadList";
	BattleSquad* battlesquad = new BattleSquad(str(boost::format("%1%/%2%")%path%squadid));
	mSquadList.insert(std::make_pair(battlesquad->getSquadId(), battlesquad));
	if(!battlesquad->init(str(boost::format("StaticData/SquadData/%1%")%suqadtypeid),
							team, unitnum, x, y, 0))
	{
		BattleSquadIte ite = mSquadList.find(battlesquad->getSquadId());
		delete battlesquad;
		mSquadList.erase(ite);
		return false;
	}
	suqadgrapmanager->createSquadGrap(battlesquad->getSquadId(), battlesquad->getPath(), battlesquad->getGridX(), battlesquad->getGridY(), 
										battlesquad->getDirection(), battlesquad->getFormation(), battlesquad->getUnitGrapNum());
	SquadGraphics* grap = suqadgrapmanager->getSquad(battlesquad->getSquadId());
	grap->setVisible(false);
	if(battlesquad->getViewbyPlayer())
	{
		CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(battlesquad, SQUAD_STATE_VISIBLE, "none",1));
	}
	return true;
}

void BattleSquadManager::removeSquad(std::string squadid)
{
	BattleSquad* battlesquad = getBattleSquad(squadid);
	if(battlesquad)
	{
		battlesquad->setUnitNum(0);
		CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(battlesquad, SQUAD_STATE_VISIBLE, "none",0));
	}
}