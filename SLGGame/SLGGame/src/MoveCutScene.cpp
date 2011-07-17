#include "MoveCutScene.h"

#include "SquadGrapManager.h"

#include "Terrain.h"

#include "CameraContral.h"

MoveCutScene::MoveCutScene(unsigned int id,std::vector<Ogre::Vector2>& grids,Ogre::Vector2& currentGrid)
{

	vectors.clear();
	quaternions.clear();
	directions.clear();
	
	Ogre::Vector2 current=currentGrid;
	int index=0;
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);

	//路径点查找算法
	for(std::vector<Ogre::Vector2>::iterator it=grids.begin();it!=grids.end();it++)
	{
		//取得当前位置与目标格的差值
		Ogre::Vector2 diffGrid=(*it)-current;
		
		//确定位置
		float wx=0,wy=0,height=0;

		if (it+1==grids.end())//如果为最后一个节点
		{
			Terrain::getSingletonPtr()->getWorldCoords((*it).x,(*it).y,wx,wy);//移动到最后一个节点的中心
			//height=Terrain::getSingletonPtr()->getHeight(wx,wy);

			Ogre::Vector3 v(wx,height,wy);
			mEndPosition=v;
			vectors[index]=v;
		}
		else
		{
			Terrain::getSingletonPtr()->getWorldCoords(current.x,current.y,wx,wy);
			//height=Terrain::getSingletonPtr()->getHeight(wx,wy);

			Ogre::Vector3 v(wx+diffGrid.x*(TILESIZE),height,wy+diffGrid.y*(TILESIZE));
			vectors[index]=v;
		}
		
		//确定方向
		Ogre::Quaternion q;
		if (diffGrid.x==0 && diffGrid.y==-1)//北
		{
			q.FromAngleAxis(Ogre::Degree(180),Ogre::Vector3(0,1,0));
			mDirection=North;
		}
		else if (diffGrid.x==0 && diffGrid.y==1)//南
		{
			q.FromAngleAxis(Ogre::Degree(0),Ogre::Vector3(0,1,0));
			mDirection=South;
		}
		else if (diffGrid.x==-1 && diffGrid.y==0)//东
		{
			q.FromAngleAxis(Ogre::Degree(270),Ogre::Vector3(0,1,0));
			mDirection=West;
		}
		else if (diffGrid.x==1 && diffGrid.y==0)//西
		{
			q.FromAngleAxis(Ogre::Degree(90),Ogre::Vector3(0,1,0));
			mDirection=East;
		}
		
		quaternions[index]=q;

		directions[index]=mDirection;
		
		current=(*it);
		index++;
	}

}

MoveCutScene::~MoveCutScene(void)
{
}

bool MoveCutScene::endCutScene()
{
	return mSquadGraphics->isTransformOver();
}

void MoveCutScene::skipCutScene()
{
	mSquadGraphics->stopTransform();
	mSquadGraphics->setGrid(mEndPosition.x,mEndPosition.y);
	mSquadGraphics->setDirection(mDirection,false);
}

void MoveCutScene::updateCutScene( unsigned int deltaTime )
{
	if(mSquadGraphics->getVisible())
	{
		Ogre::Vector3 pos = mSquadGraphics->getLeaderPosition();
		CameraContral::getSingleton().moveCameraTo(pos.x,pos.z);
	}

}

void MoveCutScene::startCutScence()
{
	mSquadGraphics->setMovePath(vectors,quaternions,directions);
}
