#include "SquadGrapManager.h"

#include "SquadGraphics.h"
#include "DataLibrary.h"

#include "Core.h"
#include "BillboardManager.h"

SquadGrapManager::SquadGrapManager(Ogre::SceneManager* sceneMgr)/*:unitIndex(0)*/
{
	mBBManager=new BillboardManager(Core::getSingletonPtr()->mCamera);
}

SquadGrapManager::~SquadGrapManager(void)
{
	clear();
	delete BillboardManager::getSingletonPtr();
}

void SquadGrapManager::clear()
{
// 	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
// 	{
// 		delete (*it);
// 	}
// 	mUnitList.clear();
	std::map<std::string, SquadGraphics*>::iterator ite;
	for(ite = mSquadGrapMap.begin(); ite != mSquadGrapMap.end(); ite++)
	{
		delete ite->second;
	}
	mSquadGrapMap.clear();
}

// SquadGraphics* SquadGrapManager::createSquad( std::string unitName,std::string datapath,unsigned int id,int x,int y,Direction d,Formation f,int soldierCount)
// {
// 	SquadGraphics* squadGrap=new SquadGraphics(unitName,datapath,Ogre::Vector2(x,y),d,f,id,soldierCount);
// 
// 	mUnitList.push_back(squadGrap);
// 
// 	return squadGrap;
// }

// void SquadGrapManager::destorySquad(unsigned int id)
// {
// 	//将队列中的进行消除
// 	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
// 	{
// 		if ((*it)->mID==id)
// 		{
// 			delete (*it);
// 			mUnitList.erase(it);
// 			break;
// 		}
// 	}
// }
// 
void SquadGrapManager::update(unsigned int deltaTime)
{
// 	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
// 	{
// 		(*it)->update(deltaTime);
// 	}
	std::map<std::string, SquadGraphics*>::iterator ite;
	for(ite = mSquadGrapMap.begin(); ite != mSquadGrapMap.end(); ite++)
	{
		ite->second->update(deltaTime);
	}
	mBBManager->update(deltaTime);
}

// SquadGraphics* SquadGrapManager::getSquad( unsigned int id )
// {
// 	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
// 	{
// 		if ((*it)->mID==id)
// 		{
// 			return (*it);
// 		}
// 	}
// 	return NULL;
// }

// void SquadGrapManager::setParticleVisible(bool visible)
// {
// 	for (std::vector<SquadGraphics*>::iterator it=mUnitList.begin();it!=mUnitList.end();it++)
// 	{
// 		(*it)->setParticleVisible(visible);
// 	}
// }


bool SquadGrapManager::createSquadGrap(std::string squadid, std::string datapath, int gridx, int gridy, int direction, int formation, int soldierCount)
{
	std::map<std::string, SquadGraphics*>::iterator ite;
	ite = mSquadGrapMap.find(squadid);
	if(ite != mSquadGrapMap.end())
		return false;
	SquadGraphics* squadGrap = new SquadGraphics(squadid, datapath, gridx, gridy, direction, formation, soldierCount);
	mSquadGrapMap.insert(std::make_pair(squadid, squadGrap));
	return true;
}

void SquadGrapManager::destorySquad(std::string squadid)
{
	std::map<std::string, SquadGraphics*>::iterator ite;
	ite = mSquadGrapMap.find(squadid);
	if(ite == mSquadGrapMap.end())
		return;
	delete ite->second;
	mSquadGrapMap.erase(ite);
}

SquadGraphics* SquadGrapManager::getSquad(std::string squadid)
{
	std::map<std::string, SquadGraphics*>::iterator ite;
	ite = mSquadGrapMap.find(squadid);
	if(ite == mSquadGrapMap.end())
		return NULL;
	return ite->second;
}

void SquadGrapManager::clearBBState()
{
	std::map<std::string, SquadGraphics*>::iterator ite;
	for(ite = mSquadGrapMap.begin(); ite != mSquadGrapMap.end(); ite++)
	{
		ite->second->setSquadBillBoardState(true);
	}
}

void SquadGrapManager::hideSquad()
{
	std::map<std::string, SquadGraphics*>::iterator ite;
	for(ite = mSquadGrapMap.begin(); ite != mSquadGrapMap.end(); ite++)
	{
		ite->second->setVisible(false);
	}
}