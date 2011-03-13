#include "SquadGrapManager.h"

#include "DataLibrary.h"

SquadGrapManager::SquadGrapManager(Ogre::SceneManager* sceneMgr):unitIndex(0)
{
}

SquadGrapManager::~SquadGrapManager(void)
{
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		destoryUnit((*it));
	}
}

SquadGraphics* SquadGrapManager::createUnit( std::string unitName,int x,int y )
{
	SquadGraphics* squadGrap=new SquadGraphics(unitName,unitIndex);

	mUnitList.push_back(squadGrap);
	unitIndex++;

	return squadGrap;
}

void SquadGrapManager::destoryUnit( SquadGraphics* unit )
{
	//将队列中的进行消除
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		if (unit==(*it))
		{
			mUnitList.erase(it);
		}
	}

	delete unit;
}

void SquadGrapManager::update(unsigned int deltaTime)
{
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		(*it)->update(deltaTime);
	}
}

