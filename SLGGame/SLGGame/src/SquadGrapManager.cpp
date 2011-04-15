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

SquadGraphics* SquadGrapManager::createSquad( std::string unitName,std::string datapath,unsigned int id,int x,int y,Direction d,Formation f )
{
	SquadGraphics* squadGrap=new SquadGraphics(unitName,datapath,Ogre::Vector2(x,y),d,f,id);

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
			break;
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

