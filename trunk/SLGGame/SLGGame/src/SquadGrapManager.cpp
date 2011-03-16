#include "SquadGrapManager.h"

#include "SquadGraphics.h"
#include "DataLibrary.h"

SquadGrapManager::SquadGrapManager(Ogre::SceneManager* sceneMgr):unitIndex(0)
{
}

SquadGrapManager::~SquadGrapManager(void)
{
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		delete (*it);
	}
	mUnitList.clear();
}

SquadGraphics* SquadGrapManager::createSquad( std::string unitName,unsigned int id,int x,int y,Direction d )
{
	SquadGraphics* squadGrap=new SquadGraphics(unitName,Ogre::Vector2(x,y),(SquadGraphics::Direction)d,id);

	mUnitList.push_back(squadGrap);

	return squadGrap;
}

void SquadGrapManager::destorySquad(unsigned int id)
{
	//将队列中的进行消除
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		if ((*it)->mID==id)
		{
			delete (*it);
			mUnitList.erase(it);
		}
	}
}

void SquadGrapManager::update(unsigned int deltaTime)
{
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		(*it)->update(deltaTime);
	}
}

SquadGraphics* SquadGrapManager::getSquad( unsigned int id )
{
	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
	{
		if ((*it)->mID==id)
		{
			return (*it);
		}
	}
	return NULL;
}

