#include "BattleSquadManager.h"

#include "AVGSquadManager.h"
#include "SquadGrapManager.h"
#include "MapDataManager.h"

#include "DataLibrary.h"

#include "BattleSquad.h"

#include "LuaSystem.h"

#include "cutscene.h"
#include "DirectionCutScene.h"
#include "SquadDeadCutScene.h"
#include "AnimationCutScene.h"
#include "SquadStateCutScene.h"

BattleSquadManager::BattleSquadManager()
{
	mCurid = 0;
	mCutSceneQueue = NULL;
	mLastCutScene = NULL;
}
BattleSquadManager::~BattleSquadManager()
{

}


void BattleSquadManager::deployConfirm()
{
	while(mDeployList.size() > 0)
	{
		BattleSquad* suqad = mDeployList.back();
		mDeployList.pop_back();
		mSquadList.push_back(suqad);
	}
}

bool  BattleSquadManager::allDeployed()
{
	BattleSquadIte ite;
	for(ite = mDeployList.begin(); ite != mDeployList.end(); ite++)
	{
		int x;
		(*ite)->getCrood(&x, NULL);
		if(x < 0)
			return false;
	}
	return true;
}

BattleSquad* BattleSquadManager::getBattleSquad(std::string id)
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		if(id == (*ite)->getId() && (*ite)->IsEliminated() == false)
			return (*ite);
	}
	for(ite = mDeployList.begin(); ite != mDeployList.end(); ite++)
	{
		if(id == (*ite)->getId())
			return (*ite);
	}
	return NULL;
}

BattleSquad* BattleSquadManager::getBattleSquadAt(int x, int y, int team, bool visibleonly)
{
	BattleSquadManager::BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		if((*ite)->IsEliminated())
			continue;
		int xx,yy;
		(*ite)->getCrood(&xx,&yy);
		if(xx ==x && yy == y)
		{
			if(!visibleonly)
				return (*ite);
			if((*ite)->viewbyTeam(team))
				return (*ite);
			return NULL;
		}
	}
	for(ite = mDeployList.begin(); ite != mDeployList.end(); ite++)
	{
		int xx,yy;
		(*ite)->getCrood(&xx,&yy);
		if(xx ==x && yy == y)
		{
			return (*ite);
		}
	}
	return NULL;
}

void BattleSquadManager::moveSquad(BattleSquad* squad,std::vector<int> pointlist, int &stopedpoint, int &eventtype)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	for(stopedpoint = 0; stopedpoint * 2 < pointlist.size();stopedpoint++)
	{
		//移动条件判断
		int x = pointlist[stopedpoint*2];
		int y = pointlist[stopedpoint*2 + 1];
		int xx,yy;
		squad->getCrood(&xx, &yy);
		if( abs(xx -x) + abs(yy -y) != 1)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( !mapdata->getPassable(x,y, squad->getTeam()))
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( getBattleSquadAt(x,y,squad->getTeam(), false) != NULL)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		if( getBattleSquadAt(x,y,squad->getTeam(), true) != NULL)
		{
			eventtype |= MOVEEVENT_AMBUSH;
			//被埋伏效果
			return;
		}
		float apcost;
		float apleft = squad->getActionPoint();
		std::string horse;
		DataLibrary::getSingleton().getData(squad->getPath() + std::string("/HorseId"),horse);
		if(horse == "none")
			apcost = mapdata->getInfApCost(x,y,0);
		else
			apcost = mapdata->getCavApCost(x,y,0);
		if(apleft<apcost)
		{
			eventtype |= MOVEEVENT_WRONG;
			return;
		}
		//移动一步
		squad->setCrood(x,y);
		DataLibrary::getSingleton().setData(squad->getPath() + std::string("/ActionPoint"),apleft - apcost);
		if(x < xx)
			squad->setDirection(West);
		else if(x > xx)
			squad->setDirection(East);
		else if( y > yy)
			squad->setDirection(South);
		else
			squad->setDirection(North);
		//计算冲锋
		
		//重新可视范围
		BattleSquadManager::BattleSquadIte ite;
		int team = squad->getTeam();
		int faction =squad->getTeamFaction(team);
		for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
		{
			if((*ite)->getTeamFaction((*ite)->getTeam()) == faction)
				continue;
			int x1,y1;
			(*ite)->getCrood(&x1,&y1);
			if(!(*ite)->viewbyTeam(team))
			{
				int range = abs(x - x1) + abs(y - y1);
				int ditectrange = (int)squad->getAttr(ATTR_DETECTION,ATTRCALC_FULL,squad->getDirection());
				int covert = (int)(*ite)->getAttr(ATTR_COVERT,ATTRCALC_FULL,squad->getDirection());
				if(range <= ditectrange - covert)
				{
					(*ite)->setViewbyTeam(team,true);
					eventtype != MOVEEVENT_SPOT;
					if(faction == 0)
					{
						setCutScene(new SquadStateCutScene((*ite),SQUAD_STATE_VISIBLE,"none",1));
					}
				}
			}
			if(!squad->viewbyTeam((*ite)->getTeam()))
			{
				int range = abs(x - x1) + abs(y - y1);
				int covert = (int)squad->getAttr(ATTR_COVERT,ATTRCALC_FULL,squad->getDirection());
				int ditectrange = (int)(*ite)->getAttr(ATTR_DETECTION,ATTRCALC_FULL,squad->getDirection());
				if(range <= ditectrange - covert)
				{
					squad->setViewbyTeam((*ite)->getTeam(),true);
					squad->setAmbushTeam((*ite)->getTeam(),true);
					if(faction == 0)
					{
						setCutScene(new SquadStateCutScene(squad,SQUAD_STATE_VISIBLE,"none",1));
					}
				}
			}
		}
	}
}

CutScene* BattleSquadManager::useSkillOn(BattleSquad* attacksquad, BattleSquad* targetsquad, std::string skillid)
{
	if(attacksquad == NULL || targetsquad == NULL )
		return NULL;
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string skillpath = attacksquad->getPath() + std::string("/SkillTable/") + skillid;
	int cooldown;
	bool re = datalib->getData(skillpath + std::string("/CoolDown"),cooldown);
	if(!re || cooldown > 0)
		return NULL;
	int aptype;
	std::string skillinfopath = std::string("StaticData/SkillData/")+ skillid;
	re = datalib->getData(skillinfopath+ std::string("/APType"),aptype);
	if(!re)
		return NULL;
	float apcost;
	datalib->getData(skillinfopath+ std::string("/APCost"),apcost);
	apcost += attacksquad->getActionPointCost(aptype);
	float apleft = attacksquad->getActionPoint();
	if(apleft < apcost)
		return NULL;
	SkillType skilltype;
	datalib->getData(skillinfopath + std::string("/Type"),skilltype);
	if(skilltype == SKILLTYPE_PASSIVE || skilltype == SKILLTYPE_TARGETAREA || skilltype == SKILLTYPE_TARGETLINE)
		return NULL;
	int minrange;
	int maxrange; 
	datalib->getData(skillinfopath + std::string("/MaxRange"),maxrange);
	datalib->getData(skillinfopath + std::string("/MinRange"),minrange);
	int targetx, targety, casterx,castery;
	attacksquad->getCrood(&casterx, &castery);
	targetsquad->getCrood(&targetx, &targety);
	int dist = abs(casterx - targetx) + abs(castery - targety);
	if(dist > maxrange || dist < minrange)
		return NULL;
	mCutSceneQueue = NULL;
	mLastCutScene = NULL;
	std::string skillscript;
	datalib->getData(skillinfopath + std::string("/Script"),skillscript);
	//设置脚本上下文
	datalib->setData(skillpath + std::string("/ScriptContext/skillcast"),0);
	datalib->setData(skillpath + std::string("/ScriptContext/skillcaster"),attacksquad->getId());
	datalib->setData(skillpath + std::string("/ScriptContext/skillcasterpath"),attacksquad->getPath());
	datalib->setData(skillpath + std::string("/ScriptContext/skilltarget"),targetsquad->getId());
	datalib->setData(skillpath + std::string("/ScriptContext/skilltargetpath"),targetsquad->getPath());
	re = LuaSystem::getSingleton().executeFunction(skillscript, "useskill" , skillpath + std::string("/ScriptContext"));
	if(!re)
		return NULL;
	int skillcast;
	datalib->getData(skillpath + std::string("/ScriptContext/skillcast"),skillcast);
	if(skillcast == 1)
	{
		//技能消耗
		datalib->setData(attacksquad->getPath() + std::string("/ActionPoint"),apleft - apcost);
		if(aptype == SKILLAPTYPE_SETUP)
			datalib->setData(attacksquad->getPath() + std::string("/APSetup"),attacksquad->getActionPointCost(aptype) +2.0f);
		else
			datalib->setData(attacksquad->getPath() + std::string("/APBattle"),attacksquad->getActionPointCost(aptype) +2.0f);
		int skillcooldown;
		datalib->getData(skillinfopath + std::string("/CoolDown"),skillcooldown);
		datalib->setData(skillpath + std::string("/CoolDown"),skillcooldown);
	}
	return getCutScene();
}

CutScene* BattleSquadManager::useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid)
{
	return NULL;
}

bool BattleSquadManager::meleeAttackSquad(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	//设置小队朝向
	Direction d;
	int targetx, targety, casterx,castery;
	attacksquad->getCrood(&casterx, &castery);
	defenesquad->getCrood(&targetx, &targety);
	if(!(casterx == targetx && castery == targety))
	{
		float k;
		if(targety-castery == 0)
			k = 2.0f;
		else
			k = abs(targetx -casterx)/ abs(targety - castery);
		if( targety > castery && k <= 1.0f)
			d = South;
		else if( targety < castery && k <= 1.0f)
			d = North;
		else if( targetx > casterx )
			d = East;
		else
			d = West;
		if(attacksquad->getDirection() != d)
		{
			attacksquad->setDirection(d);
			DirectionCutScene* dcutscene = new DirectionCutScene(attacksquad->getGrapId(), d);
			setCutScene(dcutscene);
		}
	}
	float atkint = attacksquad->getAttr(ATTR_INITIATIVE, ATTRCALC_FULL,attacksquad->getDirection());
	float defint = defenesquad->getAttr(ATTR_INITIATIVE, ATTRCALC_FULL,defenesquad->getDirection());
	BattleSquad* squad = NULL;
	if(atkint>=defint)
		squad = attacksquad;
	else
		squad = defenesquad;
	for(int n = 0; n < 2; n++)
	{
		std::vector<int> atkrolls = squad->getAttackRolls(false,squad == defenesquad,d);
		if(squad == attacksquad)
			squad = defenesquad;
		else
			squad = attacksquad;
		if(atkrolls.size() > 0)
		{
			int squadugb = squad->getUnitGrapNum();
			squad->applyAttackRolls(false, d, atkrolls);
			int squaduga = squad->getUnitGrapNum();
			if(squaduga < squadugb)
			{
				setCutScene(new SquadDeadCutScene(squad->getGrapId(), squadugb - squaduga));
			}
		}
	}
	return true;
}

void BattleSquadManager::setCutScene(CutScene* cutscene)
{
	if(mCutSceneQueue == NULL)
	{
		mCutSceneQueue = cutscene;
		mLastCutScene = cutscene;
	}
	else
	{
		mLastCutScene->setNextScene(cutscene);
		mLastCutScene = cutscene;
	}
}

void BattleSquadManager::rangedAttackCutScene(BattleSquad* attacksquad, int x, int y, UnitType castunit , std::string castparticle, std::string castaction, std::string castsound, int missiletype, std::string missileres, std::string hitparticle,std::string hitsound)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	//设置小队朝向
	Direction d;
	int casterx,castery;
	attacksquad->getCrood(&casterx, &castery);
	if(!(casterx == x && castery == y))
	{
		float k;
		if(y-castery == 0)
			k = 2.0f;
		else
			k = abs(x -casterx)/ abs(y - castery);
		if( y > castery && k <= 1.0f)
			d = South;
		else if( y < castery && k <= 1.0f)
			d = North;
		else if( x > casterx )
			d = East;
		else
			d = West;
		if(attacksquad->getDirection() != d)
		{
			attacksquad->setDirection(d);
			DirectionCutScene* dcutscene = new DirectionCutScene(attacksquad->getGrapId(), d);
			setCutScene(dcutscene);
		}
	}
	setCutScene(new AnimationCutScene(attacksquad->getGrapId(),castunit,castaction,castsound,castparticle,false, true));
}

bool BattleSquadManager::dealMagicDamage(BattleSquad* attacksquad, BattleSquad* defenesquad, int attacktime, float atk)
{
	std::vector<int> attackrolls;
	for(int n = 0; n < attacktime; n++)
	{
		int atkroll = rand()% ATKROLL;
		if(atkroll == ATKROLL -1)
			atkroll = 100;
		else if(atkroll == 0)
			atkroll = -100;
		attackrolls.push_back(atk +atkroll);
	}
	if(attackrolls.size() > 0)
	{
		int squadugb = defenesquad->getUnitGrapNum();
		Direction d = defenesquad->getDirection();
		defenesquad->applyAttackRolls(true, d, attackrolls);
		int squaduga = defenesquad->getUnitGrapNum();
		if(squaduga < squadugb)
		{
			setCutScene(new SquadDeadCutScene(defenesquad->getGrapId(), squadugb - squaduga));
		}
		return true;
	}
	return false;
}

bool BattleSquadManager::dealRangedDamage(BattleSquad* attacksquad, BattleSquad* defenesquad)
{
	Direction d = attacksquad->getDirection();
	std::vector<int> atkrolls = attacksquad->getAttackRolls(true,false,d);
	if(atkrolls.size() > 0)
	{
		int squadugb = defenesquad->getUnitGrapNum();
		d = defenesquad->getDirection();
		defenesquad->applyAttackRolls(true, d, atkrolls);
		int squaduga = defenesquad->getUnitGrapNum();
		if(squaduga < squadugb)
		{
			setCutScene(new SquadDeadCutScene(defenesquad->getGrapId(), squadugb - squaduga));
		}
		return true;
	}
	return false;
}

CutScene* BattleSquadManager::getCutScene()
{
	CutScene* cutscene = mCutSceneQueue;
	mCutSceneQueue = NULL;
	mLastCutScene = NULL;
	return cutscene;
}