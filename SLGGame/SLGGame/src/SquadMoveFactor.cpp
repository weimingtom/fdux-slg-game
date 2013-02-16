#include "SquadMoveFactor.h"

#include "BattleSquad.h"
#include "MapDataManager.h"

//SquadMoveClosetoPathFactor
SquadMoveClosetoPathFactor::SquadMoveClosetoPathFactor(std::map<int, BattleSquadManager::MoveNode>* area,
													   std::map<int, BattleSquadManager::MoveNode>* path)
:mArea(area), mPath(path),mClose(0.0f),mHighAP(0.0f)
{
	std::map<int, BattleSquadManager::MoveNode>::iterator ite = path->begin();
	for( ; ite!= mPath->end(); ite++ )
	{	
		if(ite->second.apleft > mClose)
			mClose = ite->second.apleft;
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
		ite = mArea->find(croodid);
		if(ite != mArea->end())
		{
			possibility = 0.0f - 5.0f * (mHighAP - ite->second.apleft);
		}
		else
		{
			possibility = -100.0f;
		}
	}
	return possibility;
}