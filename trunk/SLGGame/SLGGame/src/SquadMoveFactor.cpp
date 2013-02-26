#include "SquadMoveFactor.h"

#include "BattleSquad.h"
#include "MapDataManager.h"
#include "BattleSquadManager.h"
#include "CommonFunction.h"

//SquadMoveClosetoPathFactor
SquadMoveClosetoPathFactor::SquadMoveClosetoPathFactor(std::map<int, BattleSquadManager::MoveNode>* area,
													   std::map<int, BattleSquadManager::MoveNode>* path)
:mArea(area), mPath(path),mClose(0.0f),mHighAP(0.0f)
{
	std::map<int, BattleSquadManager::MoveNode>::iterator ite = path->begin();
	for( ; ite!= mPath->end(); ite++ )
	{	
		if(ite->second.apleft > mClose)
		{
			mClose = ite->second.apleft;
			mCloseCrood.mX = ite->second.x;
			mCloseCrood.mY = ite->second.y;
		}
	}
	for(ite =  mArea->begin(); ite!= mArea->end(); ite++ )
	{	
		if(ite->second.apleft > mHighAP)
			mHighAP = ite->second.apleft;
	}
}

float SquadMoveClosetoPathFactor::calcDecision(Crood &decision)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();

	float possibility = 0.0f;
	int croodid = mapdatamanager->getGridId(decision.mX, decision.mY);
	std::map<int, BattleSquadManager::MoveNode>::iterator ite = mPath->find(croodid);
	if(ite != mPath->end())
	{
		possibility = 100.0f - 10.0f * (mClose - ite->second.apleft); 
	}
	else
	{
		possibility = 100.0f - 15.0f * GetDistance(mCloseCrood.mX, mCloseCrood.mY, 
			decision.mX, decision.mY);
	}
	return possibility;
}

//HighTerrainAttrAreaFactor
HighTerrainAttrFactor::HighTerrainAttrFactor(int attrtype)
:mAttrType(attrtype)
{

}

float HighTerrainAttrFactor::calcDecision(Crood &crood)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	float possibility = 0.0f;
	switch(mAttrType)
	{
	case 0:
		possibility += 25.0f * mapdata->getDefModify(crood.mX, crood.mY, -1);
		break;
	case 1:
		possibility += 25.0f * mapdata->getCovert(crood.mX, crood.mY, -1);
		break;
	case 2:
		possibility += 25.0f * (mapdata->getInfApCost(crood.mX, crood.mY, -1) - 2.0f);
		break;
	case 3:
		possibility += 25.0f * (mapdata->getCavApCost(crood.mX, crood.mY, -1) - 2.0f);
		break;
	}
	return possibility;
}

//CloseToEnemyFactor
CloseToEnemyFactor::CloseToEnemyFactor(int faction, bool avoidsurround)
:mFaction(faction),mAvoidSurround(avoidsurround)
{
	
}

float CloseToEnemyFactor::calcDecision(Crood &crood)
{
	float possibility = 0.0f;
	BattleSquadManager* battlemgr = BattleSquadManager::getSingletonPtr();
	int x[4] = {crood.mX - 1, crood.mX, crood.mX, crood.mX + 1};
	int y[4] = {crood.mY, crood.mY - 1, crood.mY + 1, crood.mY};
	for(unsigned int n = 0; n < 4; n++)
	{
		BattleSquad* squad = battlemgr->getBattleSquadAt(x[n], y[n], mFaction, true);
		if(squad && squad->getFaction() != mFaction)
		{
			if(possibility < 0.01f)
			{
				possibility = 100.0f;
			}
			else if(mAvoidSurround)
			{
				possibility -= 25.0f;
			}
		}
	}
	return possibility;
}