#include "MoveCutScene.h"

#include "SquadGrapManager.h"

#include "Terrain.h"

#include "CameraContral.h"

MoveCutScene::MoveCutScene(std::string id,std::vector<Ogre::Vector2>& grids,Ogre::Vector2& currentGrid)
{

	vectors.clear();
	quaternions.clear();
	directions.clear();
	
	Ogre::Vector2 current=currentGrid;
	int index=0;
	mSquadGraphics=SquadGrapManager::getSingletonPtr()->getSquad(id);
	
	std::vector<Ogre::Vector2> mGrids;
	mGrids.push_back(currentGrid);
	for(std::vector<Ogre::Vector2>::iterator itt=grids.begin();itt!=grids.end();itt++)
	{
		mGrids.push_back((*itt));
	}

	Ogre::Quaternion q;
	Ogre::Vector3 position;
	//路径点查找算法
	std::vector<Ogre::Vector2>::iterator itr=mGrids.begin();
	for(std::vector<Ogre::Vector2>::iterator it=mGrids.begin();it!=mGrids.end();it++)
	{
		
		//确定位置
		float wx=0,wy=0,height=0;
		itr++;

		if (itr==mGrids.end())//如果为最后一个节点
		{
			Terrain::getSingletonPtr()->getWorldCoords((*it).x,(*it).y,wx,wy);//移动到最后一个节点的中心
			//height=Terrain::getSingletonPtr()->getHeight(wx,wy);

			Ogre::Vector3 v(wx,height,wy);
			mEndPosition.x=(*it).x;
			mEndPosition.y=(*it).y;
			position=v;
			
		}
		else
		{
			//取得当前位置与目标格的差值
			Ogre::Vector2 diffGrid=(*(itr))-(*it);
			Terrain::getSingletonPtr()->getWorldCoords((*it).x,(*it).y,wx,wy);
			//height=Terrain::getSingletonPtr()->getHeight(wx,wy);

			Ogre::Vector3 v(wx,height,wy);
			position=v;

			//确定方向
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
			else if (diffGrid.x==-1 && diffGrid.y==0)//西
			{
				q.FromAngleAxis(Ogre::Degree(270),Ogre::Vector3(0,1,0));
				mDirection=West;
			}
			else if (diffGrid.x==1 && diffGrid.y==0)//东
			{
				q.FromAngleAxis(Ogre::Degree(90),Ogre::Vector3(0,1,0));
				mDirection=East;
			}

		}

		/*if (it+1!=grids.end())//判断是不是拐角
		{
			Ogre::Vector2 diff=(*(it+1))-(*it);
			
			if (mDirection==North)
			{
				if (diff.x==1 && diff.y==0)//东
				{
					//q.FromAngleAxis(Ogre::Degree(135),Ogre::Vector3(0,1,0));
					//mDirection=NorthEast;
					if()
					current=(*it);
				}
				if (diff.x==-1 && diff.y==0)//西
				{
					//q.FromAngleAxis(Ogre::Degree(225),Ogre::Vector3(0,1,0));
					//mDirection=WestNorth;
					current=(*it);
					continue;
				}
			}

			if (mDirection==East)
			{
				if (diff.x==0 && diff.y==1)//北
				{
					//q.FromAngleAxis(Ogre::Degree(45),Ogre::Vector3(0,1,0));
					//mDirection=EastSouth;
					current=(*it);
					continue;
				}
				if (diff.x==0 && diff.y==-1)//南
				{
					//q.FromAngleAxis(Ogre::Degree(135),Ogre::Vector3(0,1,0));
					//mDirection=NorthEast;
					current=(*it);
					continue;
				}
			}

			if (mDirection==South)
			{
				if (diff.x==1 && diff.y==0)//
				{
					//q.FromAngleAxis(Ogre::Degree(45),Ogre::Vector3(0,1,0));
					//mDirection=EastSouth;
					current=(*it);
					continue;
				}
				if (diff.x==-1 && diff.y==0)//
				{
					//q.FromAngleAxis(Ogre::Degree(315),Ogre::Vector3(0,1,0));
					//mDirection=SouthWest;
					current=(*it);
					continue;
				}
			}

			if (mDirection==West)
			{
				if (diff.x==0 && diff.y==1)//
				{
					//q.FromAngleAxis(Ogre::Degree(315),Ogre::Vector3(0,1,0));
					//mDirection=SouthWest;
					current=(*it);
					continue;
				}
				if (diff.x==0 && diff.y==-1)//
				{
					//q.FromAngleAxis(Ogre::Degree(225),Ogre::Vector3(0,1,0));
					//mDirection=WestNorth;
					current=(*it);
					continue;
				}
			}
		}*/
		

		//记录位置
		quaternions[index]=q;
		
		vectors[index]=position;

		directions[index]=mDirection;
		
		current=(*it);

		index++;
	}

}

MoveCutScene::~MoveCutScene(void)
{
	//mSquadGraphics->stopTransform();
	//mSquadGraphics->setGrid(mEndPosition.x,mEndPosition.y);
	//mSquadGraphics->setDirection(mDirection,false);
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
