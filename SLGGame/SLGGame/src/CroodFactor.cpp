#include "CroodFactor.h"

#include "CommonFunction.h"
#include "MapDataManager.h"

//ClosetoCroodFactor
ClosetoCroodFactor::ClosetoCroodFactor(Crood tgtcrood, int dist)
:mTgtCrood(tgtcrood),mDist(dist)
{

}

float ClosetoCroodFactor::calcDecision(Crood &crood)
{
	float possibility = 100.0f;
	int dist = GetDistance(crood.mX, crood.mY, mTgtCrood.mX, mTgtCrood.mY) - mDist;
	possibility -= abs(dist) * 10.0f;
	return possibility;
}

//ClosetoBorderFactor
ClosetoBorderFactor::ClosetoBorderFactor(Area &area)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	std::vector<Crood> croodvec = area.getCroodVec();
	std::vector<Crood>::iterator ite = croodvec.begin();
	for( ; ite != croodvec.end(); ite++ )
	{
		if((*ite).mX < -1 || (*ite).mY < -1 || (*ite).mX > mapsize || (*ite).mY > mapsize)
		{
			continue;
		}
		mAreaSet.insert(mapdata->getGridId((*ite).mX, (*ite).mY));
	}
}

float ClosetoBorderFactor::calcDecision(Crood &crood)
{
	int close = 2;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	for(int x = crood.mX - 2; x <= crood.mX + 2; x++)
	{
		for(int y = crood.mY- 2; y <= crood.mY + 2; y++)
		{
			bool out = false;
			if(x < -1 || y < -1 || x > mapsize || y > mapsize)
			{
				out = true;
			}
			else
			{
				int id = mapdata->getGridId(x, y);
				std::set<int>::iterator ite = mAreaSet.find(id);
				if(mAreaSet.end() == ite)
				{
					out = true;
				}
			}
			int dist = GetDistance(x, y, crood.mX, crood.mY);
			if(dist < close )
				close = dist;
		}
	}
	return 100.0f - 50.0f * close;
}