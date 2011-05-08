#include "BattlePlayerState.h"

#include "GUISystem.h"
#include "GUIBattle.h"
#include "Core.h"
#include "InputControl.h"
#include "GUISquadWindows.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "CameraContral.h"
#include "GUIGameStateWindows.h"
#include "GUICommandWindows.h"
#include "GUIMenuWindow.h"
#include "Terrain.h"
#include "SquadGraphics.h"
#include "SquadGrapManager.h"
#include "cutscenediretor.h"
#include "FormationCutScence.h"
#include "DataLibrary.h"
#include "AreaGrap.h"
#include "MapDataManager.h"
#include "MoveCutScene.h"
#include "DirectionCutScene.h"

BattlePlayerState::BattlePlayerState()
{
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mCameraContral = CameraContral::getSingletonPtr();
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	Core::getSingleton().mInputControl->pushListener(this);
	mSquadWindow = static_cast<GUISquadWindows *>(mGUIBattle->getSubWindow("SquadWindow"));
	mSquadWindow->setSquad(NULL);
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	mGUICommand = static_cast<GUICommandWindows *>(mGUIBattle->getSubWindow("CommandWindow"));
	mGUICommand->setPlayerState(this);
	mGUIMenu = static_cast<GUIMenuWindow *>(mGUIBattle->getSubWindow("Menu"));
	newTurn();
	mGUIState->setAllowNextTurn(true);

	mSelectSquad = NULL;
	mState = PLAYERCONTROL_NONE;
	mMoveAreaGrap = NULL;
	mTargetAreaGrap = NULL;

	mMoveTargetX = -1;
	mMoveTargetY = -1;
	mSkillid = "none";
	mSkillTargetX = -1;
	mSkillTargetY = -1;
	mTargetSquad = NULL;
}
BattlePlayerState::~BattlePlayerState()
{
	Core::getSingleton().mInputControl->popListener();
	clearPathInfo();
	mSquadWindow->setSquad(NULL);
	mGUICommand->setSquad(NULL);
	mGUIState->setAllowNextTurn(false);
}

void BattlePlayerState::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	if(mMouseX < 20)
		dx = -1.0f;
	if(mMouseX > 1260)
		dx = 1.0f;
	if(mMouseY < 20)
		dy = -1.0f;
	if(mMouseY > 680)
		dy = 1.0f;
	mCameraContral->moveCamera(dx,dy);
}

bool BattlePlayerState::keyPressed(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattlePlayerState::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattlePlayerState::mouseMoved(const OIS::MouseEvent &arg)
{
	mMouseX = arg.state.X.abs;
	mMouseY = arg.state.Y.abs;
	mGUIBattle->SceneInputEvent(arg.state.X.abs,arg.state.Y.abs);
	int GX,GY;
	switch(mState)
	{
	case PLAYERCONTROL_MOVE:
		Terrain::getSingleton().coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
		createPath(GX,GY);
		break;
	case PLAYERCONTROL_SKILL:
		break;
	}
	return false;
}

bool BattlePlayerState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	if(mState == PLAYERCONTROL_CUTSCENE)
		return false;
	BattleSquadManager* battlemanager = BattleSquadManager::getSingletonPtr();
	if(id == OIS::MB_Left)
	{
		int GX,GY;
		Terrain::getSingletonPtr()->coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
		switch(mState)
		{
		case PLAYERCONTROL_CHOOSESKILL:

		case PLAYERCONTROL_NONE:
			for(int n = 0; n < battlemanager->mSquadList.size(); n++)
			{
				int x,y;
				battlemanager->mSquadList[n]->getCrood(&x,&y);
				if(x == GX && y == GY)
				{
					if(battlemanager->mSquadList[n]->getTeam() == 1)
					{
						mSelectSquad = battlemanager->mSquadList[n];
						mSquadWindow->setSquad(battlemanager->mSquadList[n]);
						if(battlemanager->mSquadList[n]->getActionPoint() > 0.0f)
						{
							mGUICommand->setSquad(mSelectSquad);
						}
						else
							mGUICommand->setSquad(NULL);
						mState = PLAYERCONTROL_CHOOSESKILL;
					}
				}
			}
			break;
		case PLAYERCONTROL_MOVE:
			if(mMoveAreaGrap->inArea(GX,GY))
			{
				int x,y;
				mSelectSquad->getCrood(&x,&y);
				if(x == GX && y == GY)
				{
					mGUICommand->setSquad(mSelectSquad);
					clearPathInfo();
					mState = PLAYERCONTROL_CHOOSESKILL;
				}
				else
				{
					executeMove(GX,GY);
				}
			}
			break;
		case PLAYERCONTROL_SKILL:
			break;
		}
	}
	else if(id == OIS::MB_Right)
	{
		switch(mState)
		{
		case PLAYERCONTROL_CHOOSESKILL:
			int GX,GY;
			Terrain::getSingletonPtr()->coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
			int x,y;
			mSelectSquad->getCrood(&x,&y);
			if(x != -1 && !(x == GX && y == GY))
			{
				Direction d;
				float k;
				if(GY-y == 0)
					k = 2.0f;
				else
					k = abs(GX -x)/ abs(GY - y);
				if( GY > y && k <= 1.0f)
					d = South;
				else if( GY < y && k <= 1.0f)
					d = North;
				else if( GX > x )
					d = East;
				else
					d = West;
				mSelectSquad->setDirection(d);
				int grapid = mSelectSquad->getGrapId();
				SquadGraphics* squadgrap = SquadGrapManager::getSingleton().getSquad(grapid);
				squadgrap->setDirection(d,false);
			}
			break;
		case PLAYERCONTROL_MOVE:
			mGUICommand->setSquad(mSelectSquad);
			clearPathInfo();
			mState = PLAYERCONTROL_CHOOSESKILL;
			break;
		}
	}

	return false;
}

bool BattlePlayerState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}

void BattlePlayerState::newTurn()
{
	for(int n = 0; n < mSquadManager->mSquadList.size(); n++)
	{
		if(mSquadManager->mSquadList[n]->getTeam() == 1)
			mSquadManager->mSquadList[n]->newTurn();
	}
}

void BattlePlayerState::reactiveState()
{
	if(mState == PLAYERCONTROL_CUTSCENE)
	{
		mSquadWindow->setSquad(mSelectSquad);
		if(mSelectSquad->getActionPoint() > 0.0f)
		{
			mGUICommand->setSquad(mSelectSquad);
		}
		mState = PLAYERCONTROL_CHOOSESKILL;
	}
	mGUIState->setAllowNextTurn(true);
}

void BattlePlayerState::moveSquad()
{
	int startx,starty;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	mSelectSquad->getCrood(&startx,&starty);
	std::vector<int> coordlist;
	coordlist.push_back(startx);
	coordlist.push_back(starty);
	//寻找可以移动的路径
	int n = 0;
	bool finding = true;
	while(finding)
	{
		if(n*2 < coordlist.size())
		{
			int x = coordlist[n*2];
			int y = coordlist[n*2 +1];
			float apleft;
			if(x == startx && y == starty)
				apleft = mSelectSquad->getActionPoint();
			else
			{
				MapNodeIte ite;
				ite = mMoveMap.find(x + y * mapsize);
				if(ite == mMoveMap.end())
				{
					finding = false;
					break;
				}
				else
					apleft = ite->second->mAPleft;
			}
			int xx,yy;
			float apcost = apleft;
			xx = x - 1;
			yy = y;
			bool passable = canPass(xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrew = East;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
 				else
				{
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrew = East;
				}
			}
			xx = x + 1;
			yy = y;
			apcost = apleft;
			passable = canPass(xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrew = West;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrew = West;
				}
			}
			xx = x;
			yy = y - 1;
			apcost = apleft;
			passable = canPass(xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrew = South;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrew = South;
				}
			}
			xx = x;
			yy = y + 1;
			apcost = apleft;
			passable = canPass(xx,yy, apcost);
			if(passable)
			{
				coordlist.push_back(xx);
				coordlist.push_back(yy);
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrew = North;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrew = North;
				}
			}
		}
		else
			finding = false;
		n++;
	}
	std::vector<int> movecoordlist;
	movecoordlist.push_back(startx);
	movecoordlist.push_back(starty);
	MapNodeIte movenodeite;
	for(movenodeite = mMoveMap.begin(); movenodeite != mMoveMap.end(); movenodeite++)
	{
		movecoordlist.push_back(movenodeite->second->x);
		movecoordlist.push_back(movenodeite->second->y);
	}
	mMoveAreaGrap = new AreaGrap(movecoordlist,"CUBE_BLUE");
	//生成移动路径实体
	float apleft = mSelectSquad->getActionPoint();
	for(int n = 0; n < apleft/1.0f; n++)
		mMovePathList.push_back(new MovePath);
	mGUICommand->setSquad(NULL);
	mState = PLAYERCONTROL_MOVE;
}

bool BattlePlayerState::canPass(int x, int y, float &apcost)
{
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	MapNodeIte ite;
	ite = mMoveMap.find(x + y * mapsize);
	if(ite != mMoveMap.end())
	{
		if(ite->second->mAPleft >= apcost)
			return false;
	}
	else
	{
		if(!mapdata->getPassable(x,y,0))
			return false;
		BattleSquad* blocksquad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,1,true);
		if(blocksquad)
			return false;
	}
	std::string horse;
	DataLibrary::getSingleton().getData(mSelectSquad->getPath() + std::string("/HorseId"),horse);
	float apleft = apcost;
	if(horse == "none")
		apcost = mapdata->getInfApCost(x,y,0);
	else
		apcost = mapdata->getCavApCost(x,y,0);
	if(apleft >= apcost)
		return true;
	return false;
}

void BattlePlayerState::changeFormation(Formation f)
{
	if(mState == PLAYERCONTROL_CHOOSESKILL)
	{
		float apleft = mSelectSquad->getActionPoint();
		float apcost = mSelectSquad->getActionPointCost(SKILLAPTYPE_SETUP) + 2.0f;
		if(apleft>=apcost)
		{
			apleft -= apcost;
			mSelectSquad->setFormation(f);
			DataLibrary::getSingleton().setData(mSelectSquad->getPath() + std::string("/ActionPoint"),apleft);
			DataLibrary::getSingleton().setData(mSelectSquad->getPath() + std::string("/APSetup"),apcost);
			CutSceneDirector* cutscenedirector = new CutSceneDirector;
			FormationCutScene* formcutscene = new FormationCutScene(mSelectSquad->getGrapId(), f);
			cutscenedirector->addCutScene(formcutscene);
			mMainState->PushState(cutscenedirector);
			mGUICommand->setSquad(NULL);
			mGUIState->setAllowNextTurn(false);
			mState = PLAYERCONTROL_CUTSCENE;
		}
	}
}
void BattlePlayerState::useSkill(std::string skillid)
{

}

void BattlePlayerState::clearPathInfo()
{
	MapNodeIte movenodeite;
	for(movenodeite = mMoveMap.begin(); movenodeite != mMoveMap.end(); movenodeite++)
	{
		delete movenodeite->second;
	}
	mMoveMap.clear();
	for(int n = 0; n < mMovePathList.size(); n++)
	{
		delete mMovePathList[n];
	}
	mMovePathList.clear();
	if(mMoveAreaGrap)
	{
		delete mMoveAreaGrap;
		mMoveAreaGrap = NULL;
	}
}

void BattlePlayerState::createPath(int x,int y)
{
	if(mMoveAreaGrap->inArea(x,y))
	{
		//生成路径
		int startx,starty;
		MapDataManager* mapdata = MapDataManager::getSingletonPtr();
		int mapsize = mapdata->getMapSize();
		mSelectSquad->getCrood(&startx,&starty);
		int xx = x,yy = y;
		for(int n = 0; n < mMovePathList.size(); n++)
		{
			if(xx == startx && yy == starty)
			{
				mMovePathList[n]->setVisible(false);
				continue;
			}
			mMovePathList[n]->setVisible(true);
			MapNodeIte ite;
			ite = mMoveMap.find(xx + yy * mapsize);
			if(ite == mMoveMap.end())
			{
				mMovePathList[n]->setVisible(false);
				xx = startx;
				yy = starty;
			}
			else
			{
				Direction d = ite->second->mDirectionToPrew;
				mMovePathList[n]->setPosition(xx,yy,d);
				switch(d)
				{
				case North:
					yy -= 1;
					break;
				case South:
					yy += 1;
					break;
				case East:
					xx += 1;
					break;
				case West:
					xx -= 1;
					break;
				}
			}
		}
		return;
	}
	for(int n = 0; n < mMovePathList.size(); n++)
	{
		mMovePathList[n]->setVisible(false);
	}
}

void BattlePlayerState::MovePath::setPosition(int x, int y, Direction d)
{
	float fx,fy;
	Terrain::getSingleton().getWorldCoords(x,y,fx,fy);
	mPathNode->setPosition(fx,Terrain::getSingleton().getHeight(fx,fy) + 4.0f,fy);
	switch(d)
	{
		case North:
			mPathNode->setDirection(0.01f,0.0f, 1.0f, Ogre::Node::TS_PARENT);
			break;
		case South:
			mPathNode->setDirection(0.01f,0.0f,  -1.0f, Ogre::Node::TS_PARENT);
			break;
		case East:
			mPathNode->setDirection(-1.0f,0.0f, 0.01f, Ogre::Node::TS_PARENT);
			break;
		case West:
			mPathNode->setDirection(1.0f,0.0f, 0.01f, Ogre::Node::TS_PARENT);
			break;
	}
}

void BattlePlayerState::executeMove(int x, int y)
{
	int startx,starty;
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	int mapsize = mapdata->getMapSize();
	mSelectSquad->getCrood(&startx,&starty);
	int xx = x,yy = y;
	std::vector<int> croodlistrev;
	while(xx != startx || yy !=starty)
	{
		MapNodeIte ite;
		ite = mMoveMap.find(xx + yy * mapsize);
		croodlistrev.push_back(xx);
		croodlistrev.push_back(yy);
		Direction d = ite->second->mDirectionToPrew;
		switch(d)
		{
		case North:
			yy -= 1;
			break;
		case South:
			yy += 1;
			break;
		case East:
			xx += 1;
			break;
		case West:
			xx -= 1;
			break;
		}
	}
	std::vector<int> croodlist;
	int xxx,yyy;
	while(croodlistrev.size()>0)
	{
		yyy = croodlistrev.back();
		croodlistrev.pop_back();
		xxx = croodlistrev.back();
		croodlistrev.pop_back();
		croodlist.push_back(xxx);
		croodlist.push_back(yyy);
	}
	int stoppoint;
	int evt;
	std::vector<Ogre::Vector2> movepath;
	BattleSquadManager::getSingleton().moveSquad(mSelectSquad, croodlist, stoppoint, evt);
	int n;
	for(n = 0; n *2 < croodlist.size(); n++)
	{
		if(stoppoint > n)
		{
			movepath.push_back(Ogre::Vector2(croodlist[n*2],croodlist[n*2+1]));
		}
	}
	if(stoppoint != n && (evt & MOVEEVENT_AMBUSH) > 0 )
	{
		mMoveTargetX = x;
		mMoveTargetY = y;
	}
	else
	{
		mMoveTargetX = -1;
		mMoveTargetY = -1;
	}
	MoveCutScene* movecutscene = new MoveCutScene(mSelectSquad->getGrapId(),movepath,Ogre::Vector2(startx,starty));
	DirectionCutScene* dircutscene = new DirectionCutScene(mSelectSquad->getGrapId(),mSelectSquad->getDirection());
	movecutscene->setNextScene(dircutscene);
	CutSceneDirector* cutscenedirector = new CutSceneDirector;
	cutscenedirector->addCutScene(movecutscene);
	clearPathInfo();
	mState = PLAYERCONTROL_CUTSCENE;
	mGUIState->setAllowNextTurn(false);
	mMainState->PushState(cutscenedirector);
}