#include "SquadMoveFactor.h"

#include "BattleSquad.h"
#include "MapDataManager.h"

//SquadMoveClosetoPathFactor
SquadMoveClosetoPathFactor::SquadMoveClosetoPathFactor(float scale,
													   std::map<int, BattleSquadManager::MoveNode>* area,
													   std::map<int, BattleSquadManager::MoveNode>* path)
:DecisionMapFactor(scale), mArea(area), mPath(path),mClose(0.0f)
{
	std::map<int, BattleSquadManager::MoveNode>::iterator ite = path->begin();
	for( ; ite!= path->end(); ite++ )
	{	
		if(ite->second.apleft > mClose)
			mClose = ite->second.apleft;
	}
}

void SquadMoveClosetoPathFactor::calcDecision(std::vector<DecisionInfo<Crood>> &decisionVec)
{
	MapDataManager* mapdatamanager = MapDataManager::getSingletonPtr();
	std::vector<DecisionInfo<Crood>>::iterator decite = decisionVec.begin();
	std::map<int, BattleSquadManager::MoveNode>::iterator ite = mPath->end();
	for( ; decite != decisionVec.end(); decite++)
	{
		float possibility = 0.0f;
		int croodid = mapdatamanager->getGridId((*decite).decision.mX, (*decite).decision.mY);
		ite = mPath->find(croodid);
		if(ite != mPath->end())
		{
			possibility = 100.0f - 10.0f * (mClose - ite->second.apleft); 
		}
		(*decite).possibility += possibility * mScale;
	}
}