#include "Skill.h"

#include "Driver.h"

Skill::Skill(std::string name):mName(name),mCurrTime(0)
{
}

Skill::~Skill(void)
{
}

void Skill::addObject( std::string name,Ogre::MovableObject* object,Ogre::SceneNode* node)
{
	mObjectList[name]=object;
	mNodeList[name]=node;
}

void Skill::removeObjcetAndNode( std::string name )
{
	std::map<std::string,Ogre::MovableObject*>::iterator objectItr = mObjectList.find(name);
	if (objectItr != mObjectList.end())
	{
		mObjectList.erase(objectItr);
	}

	std::map<std::string,Ogre::SceneNode*>::iterator nodeItr = mNodeList.find(name);
	if (nodeItr != mNodeList.end())
	{
		mNodeList.erase(nodeItr);
	}
}

Ogre::MovableObject* Skill::getObject( std::string name )
{
	return mObjectList[name];
}

Ogre::SceneNode* Skill::getNode( std::string name )
{
	return mNodeList[name];
}

void Skill::addDriver( std::string name,std::string datapath )
{

}

std::string Skill::getName()
{
	return mName;
}

void Skill::start()
{
	mCurrTime=0;
}

void Skill::end()
{
	mCurrTime=0;
	for (std::map<std::string,Driver*>::iterator it=mDriverList.begin();it!=mDriverList.end();it++)
	{
		delete it->second;
	}
}

void Skill::update( unsigned int time )
{
	mCurrTime+=time;

	for (std::map<std::string,Driver*>::iterator it=mDriverList.begin();it!=mDriverList.end();it++)
	{
		if(it->second->checkTime(mCurrTime))
		{
			it->second->update(time);
		}
	}
}