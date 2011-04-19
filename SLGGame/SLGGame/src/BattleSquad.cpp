#include "BattleSquad.h"

#include "DataLibrary.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "MapDataManager.h"

BattleSquad::BattleSquad(std::string id, int grapid ,int x, int y)
:mId(id),mGrapId(grapid)
{
	setCrood(x,y);
}
BattleSquad::~BattleSquad()
{

}

void BattleSquad::setCrood(int x, int y)
{
	mX = x;
	mY = y;
	SquadGrapManager::getSingleton().getSquad(mGrapId)->setGrid(mX,mY);
	std::string datapath = std::string("GameData/BattleData/SquadList/") + mId;
	DataLibrary::getSingleton().setData(datapath + std::string("/GridX"),mX);
	DataLibrary::getSingleton().setData(datapath + std::string("/GridY"),mY);
}

void BattleSquad::setDirection(Direction d)
{
	DataLibrary::getSingleton().setData(std::string("GameData/BattleData/SquadList/") + mId + std::string("/Direction"),d);
}

void BattleSquad::getCrood(int* x, int* y)
{
	if(x != NULL)
		(*x) = mX;
	if(y != NULL)
		(*y) = mY;
}

Direction BattleSquad::getDirection()
{
	Direction d;
	DataLibrary::getSingleton().getData(std::string("GameData/BattleData/SquadList/") + mId + std::string("/Direction"),d);
	return d;
}

std::string BattleSquad::getSquadName()
{
	std::string name;
	DataLibrary::getSingleton().getData(std::string("GameData/BattleData/SquadList/") + mId + std::string("/Name"),name);
	return name;
}