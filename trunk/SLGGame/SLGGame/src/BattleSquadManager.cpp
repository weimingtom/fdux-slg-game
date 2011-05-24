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

BattleSquadManager::BattleSquadManager()
{
	mCurid = 0;
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

int BattleSquadManager::getTeamRelation(int team)
{
	std::string temppath,tempstr;
	temppath = std::string("GameData/BattleData/Team/Team") + Ogre::StringConverter::toString(team) + std::string("/Relation");
	DataLibrary::getSingleton().getData(temppath,tempstr);
	if(tempstr == "alliance")
		return 0;
	else if(tempstr == "player")
		return 0;
	else if(tempstr == "enemy1")
		return 1;
	else if(tempstr == "enemy2")
		return 2;
	else if(tempstr == "enemy3")
		return 3;
	return 0;
}

BattleSquad* BattleSquadManager::getBattleSquad(std::string id)
{
	BattleSquadIte ite;
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		if(id == (*ite)->getId())
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
	int faction = getTeamRelation(team);
	for(ite = mSquadList.begin(); ite != mSquadList.end(); ite++)
	{
		int xx,yy;
		(*ite)->getCrood(&xx,&yy);
		if(xx ==x && yy == y)
		{
			if(!visibleonly)
				return (*ite);
			if((*ite)->viewbyTeam(faction))
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

		//重新可视范围等


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
	datalib->setData(skillpath + std::string("/ScriptContext/skilltarget"),targetsquad->getId());
	re = LuaSystem::getSingleton().ExecuteFunction(skillscript, "useskill" , skillpath + std::string("/ScriptContext"));
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
	return mCutSceneQueue;
}

CutScene* BattleSquadManager::useSkillAt(BattleSquad* attacksquad, int x, int y, std::string skillid)
{
	return NULL;
}

bool BattleSquadManager::meleeAttackSquad(BattleSquad* attacksquad, BattleSquad* defenesquad, int &atkdead, int &atkwound,int &defdead, int &defwound)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	int targetx, targety, casterx,castery;
	attacksquad->getCrood(&casterx, &castery);
	defenesquad->getCrood(&targetx, &targety);
	if(!(casterx == targetx && castery == targety))
	{
		Direction d;
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
	int asquadugb = attacksquad->getUnitGrapNum();
	int dsquadugb = defenesquad->getUnitGrapNum();
	int asquadunitnum, dsquadunitnum;
	datalib->getData(attacksquad->getPath() + std::string("/UnitNumber"), asquadunitnum);
	datalib->getData(defenesquad->getPath() + std::string("/UnitNumber"), dsquadunitnum);
	asquadunitnum -= 5;
	dsquadunitnum -= 10;
	asquadunitnum = (asquadunitnum < 1)? 1:asquadunitnum;
	dsquadunitnum = (dsquadunitnum < 1)? 1:dsquadunitnum;
	datalib->setData(attacksquad->getPath() + std::string("/UnitNumber"), asquadunitnum);
	datalib->setData(defenesquad->getPath() + std::string("/UnitNumber"), dsquadunitnum);
	int asquaduga = attacksquad->getUnitGrapNum();
	int dsquaduga = defenesquad->getUnitGrapNum();
	if(dsquaduga < dsquadugb)
	{
		setCutScene(new SquadDeadCutScene(defenesquad->getGrapId(), dsquadugb - dsquaduga));
	}
	if(asquaduga < asquadugb)
	{
		setCutScene(new SquadDeadCutScene(attacksquad->getGrapId(), asquadugb - asquaduga));
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