#include "AreaGrap.h"

#include "DataLibrary.h"
#include "Terrain.h"

AreaGrap::AreaGrap(std::string path, std::string mat)
:mNode(NULL),mAreaObj(NULL)
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
	creatArea(mat);
}
AreaGrap::AreaGrap(std::vector<int> coordlist, std::string mat)
:mNode(NULL),mAreaObj(NULL)
{
	mCoordList = coordlist;
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
	mAreaObj->begin(mat);
	for(int n = 0; n < mCoordList.size() / 2 ; n++)
	{
		int x = mCoordList[n * 2];
		int y = mCoordList[n * 2 + 1];
		float xx = startpos + x * TILESIZE;
		float yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx,yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx,yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + (x+1) * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + x * TILESIZE;
		yy = startpos + y * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);
		xx = startpos + x * TILESIZE;
		yy = startpos + (y+1) * TILESIZE;
		mAreaObj->position(xx, terrain->getHeight(xx, yy) + 0.5f, yy);
		mAreaObj->colour(1.0f,1.0f,1.0f);
		mAreaObj->normal(0.0f,1.0f,0.0f);		
	}
	mAreaObj->end();
	mNode->attachObject(mAreaObj);
}

bool AreaGrap::inArea(int x, int y)
{
	for(int n = 0; n < mCoordList.size() / 2 ; n++)
	{
		if(x == mCoordList[n * 2] && y == mCoordList[n * 2 + 1])
			return true;
	}
	return false;
}
