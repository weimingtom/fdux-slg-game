#include "AreaGrap.h"

#include "DataLibrary.h"
#include "Terrain.h"

AreaGrap::AreaGrap(std::string path, std::string mat, float height)
:mNode(NULL),mAreaObj(NULL),mHeight(height)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::vector<std::string> coordlist;
	std::vector<std::string>::iterator ite;
	coordlist = datalib->getChildList(path);
	for(ite = coordlist.begin(); ite != coordlist.end(); ite++)
	{
		int x,y;
		datalib->getData(path + std::string("/") + (*ite) + std::string("/X"),x);
		datalib->getData(path + std::string("/") + (*ite) + std::string("/Y"),y);
		mCoordList.push_back(x);
		mCoordList.push_back(y);
	}
	mMat = mat;
	creatArea(mat);
}
AreaGrap::AreaGrap(std::vector<int> coordlist, std::string mat, float height)
:mNode(NULL),mAreaObj(NULL),mHeight(height)
{
	mCoordList = coordlist;
	mMat = mat;
	creatArea(mat);
}
AreaGrap::~AreaGrap()
{
	mNode->detachObject(mAreaObj);
	Core::getSingleton().mSceneMgr->destroyManualObject(mAreaObj);
	Core::getSingleton().mSceneMgr->destroySceneNode(mNode);
}

void AreaGrap::creatArea(std::string mat)
{
	mNode = Core::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mAreaObj = Core::getSingleton().mSceneMgr->createManualObject();
	Terrain* terrain = Terrain::getSingletonPtr();
	float startpos;
	terrain->getWorldCoords(0,0,startpos,startpos);
	startpos -= TILESIZE /2.0f;
	mAreaObj->setDynamic(true);
	mAreaObj->begin(mat);
	for(unsigned int n = 0; n < mCoordList.size() / 2 ; n++)
	{
		int x = mCoordList[n * 2];
		int y = mCoordList[n * 2 + 1];
		float xx = startpos + x * TILESIZE;
		float yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + x * TILESIZE;
		yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + x * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);		
	}
	mAreaObj->end();
	mAreaObj->setVisibilityFlags(VISMASK_TRANSPARENT);
	mNode->attachObject(mAreaObj);
	mMaxCroodNum = mCoordList.size() / 2;
}

void AreaGrap::changeArea(std::vector<int> coordlist)
{
	float startpos;
	Terrain* terrain = Terrain::getSingletonPtr();
	terrain->getWorldCoords(0,0,startpos,startpos);
	startpos -= TILESIZE /2.0f;
	if(mMaxCroodNum == 0)
	{
		mCoordList = coordlist;
		mAreaObj->begin(mMat);
		for(unsigned int n = 0; n < mCoordList.size() / 2 ; n++)
		{
			int x = mCoordList[n * 2];
			int y = mCoordList[n * 2 + 1];
			float xx = startpos + x * TILESIZE;
			float yy = startpos + y * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);
			xx = startpos + (x+1) * TILESIZE;
			yy = startpos + (y+1) * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);
			xx = startpos + (x+1) * TILESIZE;
			yy = startpos + y * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);
			xx = startpos + (x+1) * TILESIZE;
			yy = startpos + (y+1) * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);
			xx = startpos + x * TILESIZE;
			yy = startpos + y * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);
			xx = startpos + x * TILESIZE;
			yy = startpos + (y+1) * TILESIZE;
			mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
			mAreaObj->colour(1.0f,1.0f,1.0f);
			mAreaObj->normal(0.0f,1.0f,0.0f);		
		}
		mAreaObj->end();
		mMaxCroodNum = mCoordList.size() / 2;
	}
	else
	{
		mCoordList = coordlist;
		if(coordlist.size() / 2 <= mMaxCroodNum)
		{
			mAreaObj->beginUpdate(0);
			unsigned int n = 0;
			for(; n < coordlist.size() / 2 ; n++)
			{
				int x = mCoordList[n * 2];
				int y = mCoordList[n * 2 + 1];
				float xx = startpos + x * TILESIZE;
				float yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + x * TILESIZE;
				yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + x * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);	
			}
			for(; n < mMaxCroodNum ; n++)
			{
				mAreaObj->position(startpos, terrain->getHeight(startpos,startpos) + mHeight, startpos);
				mAreaObj->position(startpos, terrain->getHeight(startpos,startpos) + mHeight, startpos);
				mAreaObj->position(startpos, terrain->getHeight(startpos, startpos) + mHeight, startpos);
				mAreaObj->position(startpos, terrain->getHeight(startpos, startpos) + mHeight, startpos);
				mAreaObj->position(startpos, terrain->getHeight(startpos, startpos) + mHeight, startpos);
				mAreaObj->position(startpos, terrain->getHeight(startpos, startpos) + mHeight, startpos);	
			}
			mAreaObj->end();
		}
		else
		{
			mMaxCroodNum = mCoordList.size() / 2;
			mAreaObj->beginUpdate(0);
			mAreaObj->estimateVertexCount(mMaxCroodNum * 6);
			for(unsigned int n = 0; n < mCoordList.size() / 2 ; n++)
			{
				int x = mCoordList[n * 2];
				int y = mCoordList[n * 2 + 1];
				float xx = startpos + x * TILESIZE;
				float yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx,yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + (x+1) * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + x * TILESIZE;
				yy = startpos + y * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);
				xx = startpos + x * TILESIZE;
				yy = startpos + (y+1) * TILESIZE;
				mAreaObj->position(xx, terrain->getHeight(xx, yy) + mHeight, yy);	
			}
			mAreaObj->end();
		}
	}
}

bool AreaGrap::inArea(int x, int y)
{
	for(unsigned int n = 0; n < mCoordList.size() / 2 ; n++)
	{
		if(x == mCoordList[n * 2] && y == mCoordList[n * 2 + 1])
			return true;
	}
	return false;
}
