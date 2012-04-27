#include "BattleSquadManager.h"

#include <algorithm>
#include <boost/format.hpp>

#include "MapDataManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"
#include "CommonFunction.h"

#include "LuaSystem.h"
#include "StringTable.h"

#include "CutSceneBuilder.h"
#include "FormationCutScence.h"
#include "MoveCutScene.h"
#include "SquadStateCutScene.h"

#include "MapDataManager.h"

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

void BattleSquadManager::turnEnd(int team)
{
	BattleSquadIte ite = mSquadList.begin();
	for(; ite != mSquadList.end(); ite++)
	{
		if(ite->second->getTeam() == team)
		{
			ite->second->turnEnd();
		}
	}
}

std::map<int, BattleSquadManager::MoveNode> BattleSquadManager::getMoveArea(BattleSquad* squad)
{
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

		squad->setGridX(x);
		squad->setGridY(y);

		m_moveList.push_back(Ogre::Vector2(x, y));

		int faction = squad->getFaction();
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
						CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(ite->second,SQUAD_STATE_VISIBLE,"none",1));
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
					squad->setViewByFaction(faction,true);
					squad->setAmbushFaction(faction,true);
					if(faction != 0)
					{
						InterruptMove();
						CutSceneBuilder::getSingleton().addCutScene(new SquadStateCutScene(squad, SQUAD_STATE_VISIBLE,"none",1));
						m_moveInterrupt = false;
						m_moveList.clear();
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

void BattleSquadManager::InterruptMove()
{
	if(m_moveList.size() > 0)
	{
		MoveCutScene* movecutscne = new MoveCutScene(m_moveSquad->getSquadId(), m_moveList, m_startPoint);
		CutSceneBuilder::getSingleton().addCutScene(movecutscne);
	}
	m_moveInterrupt = true;
}

void BattleSquadManager::changeFormation(BattleSquad* squad, enumtype formation, bool costap)
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
	std::vector<int> idlist;
	
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
									skillnode.validTarget = true;
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
			skillarea.push_back(skillnode);
		}
		break;
	case SKILLTARGETTYPE_MELEE:
		{

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
	case SKILLTARGETTYPE_MELEE:
		{

		}
		break;
	}
}

bool BattleSquadManager::dealMeleeDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk, int fluctuate)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}

bool BattleSquadManager::dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	return true;
}