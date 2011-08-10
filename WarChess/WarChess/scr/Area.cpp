#include "Area.h"

Area::Area(std::string name):mName(name)
{
	mVisable = false;
}
Area::~Area()
{
	CoordIte ite;
	for(ite = mCoordList.begin(); ite != mCoordList.end(); ite++)
		delete *(ite);
}

void Area::setVisable(bool visable)
{
	CoordIte ite;
	for(ite = mCoordList.begin(); ite != mCoordList.end(); ite++)
	{
		(*ite)->mCoordNode->setVisible(visable);
	}
	mVisable = visable;
}

void Area::addCoord(int x, int y)
{
	CoordIte ite;
	for(ite = mCoordList.begin(); ite != mCoordList.end(); ite++)
	{
		if((*ite)->x == x && (*ite)->y == y)
			return;
	}
	AreaCoord* newcoord = new AreaCoord();
	newcoord->x = x;
	newcoord->y = y;
	newcoord->mCoordEnt = IIRoot::getSingleton().mSceneMgr->createEntity("Cube.mesh");
	newcoord->mCoordEnt->setMaterialName("CUBE_RED");
	newcoord->mCoordNode = IIRoot::getSingleton().mSceneMgr->getRootSceneNode()->createChildSceneNode();
	newcoord->mCoordNode->attachObject(newcoord->mCoordEnt);
	int gridsize = IIRoot::getSingletonPtr()->mTerrain->getGridSize();
	float blocksize = IIRoot::getSingletonPtr()->mTerrain->getBlockSize();
	float xx = x * blocksize - gridsize * blocksize / 2.0f + blocksize /2.0f;
	float yy = y * blocksize - gridsize * blocksize / 2.0f + blocksize /2.0f;
	newcoord->mCoordNode->setPosition(xx,0.0f,yy);
	newcoord->mCoordNode->setVisible(mVisable);
	mCoordList.push_back(newcoord);
}

void Area::removeCoord(int x, int y)
{
	CoordIte ite;
	for(ite = mCoordList.begin(); ite != mCoordList.end(); ite++)
	{
		if((*ite)->x == x && (*ite)->y == y)
		{
			delete (*ite);
			mCoordList.erase(ite);
			return;
		}
	}
}

std::vector<int> Area::getCoordList()
{
	std::vector<int> pointlist;
	CoordIte ite;
	for(ite = mCoordList.begin(); ite != mCoordList.end(); ite++)
	{
		pointlist.push_back((*ite)->x);
		pointlist.push_back((*ite)->y);
	}
	return pointlist;
}