#pragma once

#include <Ogre.h>
#include "EntityData.h"
#include "IIRoot.h"

class ObjectData:public EntityData
{
public:
	ObjectData(QString name):EntityData(name),mNode(NULL),mEntity(NULL)
	{

	}

	~ObjectData()
	{
		if (mNode!=NULL && mEntity!=NULL)
		{
			IIRoot::getSingletonPtr()->mSceneMgr->destroySceneNode(mNode);
			IIRoot::getSingletonPtr()->mSceneMgr->destroyEntity(mEntity);
		}
	}
	
	Ogre::SceneNode* mNode;
	Ogre::Entity* mEntity;
	int GridX;
	int GridY;

};