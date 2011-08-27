#include "BattlePlayerState.h"

#include <algorithm>

#include <ogre.h>

#include <boost/format.hpp>

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
#include "GUITargetWindow.h"
#include "GUIInfoWindow.h"
#include "StringTable.h"
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
#include "BattleMessageBoxState.h"

#define SELECT_PLANE_HEIGHT_MOVE 1
#define SELECT_PLANE_HEIGHT 0.5

BattlePlayerState::BattlePlayerState()
{
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mCameraContral = CameraContral::getSingletonPtr();
	mGUIBattle = static_cast<GUIBattle *>(GUISystem::getSingleton().getScene(BattleScene));
	GUISystem::getSingletonPtr()->setFrameUpdateScene(BattleScene);
	Core::getSingleton().mInputControl->pushListener(this);
	mSquadWindow = static_cast<GUISquadWindows *>(mGUIBattle->getSubWindow("SquadWindow"));
	mSquadWindow->setSquad(NULL);
	mGUIState = static_cast<GUIGameStateWindows *>(mGUIBattle->getSubWindow("GameState"));
	mGUICommand = static_cast<GUICommandWindows *>(mGUIBattle->getSubWindow("CommandWindow"));
	mGUICommand->setPlayerState(this);
	mGUIMenu=static_cast<GUIMenuWindow *>(GUISystem::getSingleton().createScene(MenuWindowsScene));
	mMouseX = 640;
	mMouseY = 360;
	mGUIState->setAllowNextTurn(true);

	mSelectSquad = NULL;
	mState = PLAYERCONTROL_NONE;
	mMoveAreaGrap = NULL;
	mTargetAreaGrap = NULL;

	mMoveTargetX = -1;
	mMoveTargetY = -1;
	mSkillid = "none";
	mTargetSquad = NULL;
	mMeleeSkill = false;

	createSelectPlane();

}
BattlePlayerState::~BattlePlayerState()
{
	Core::getSingleton().mInputControl->popListener();
	clearPathInfo(true);
	mSquadWindow->setSquad(NULL);
	mGUICommand->setSquad(NULL);
	mGUIState->setAllowNextTurn(false);
	planeNode->setVisible(false);
}

void BattlePlayerState::update(unsigned int deltaTime)
{
	float dx = 0.0f,dy = 0.0f;
	float dt = (float)deltaTime / 5.0f;
	if(mMouseX < 20)
		dx = -dt;
	if(mMouseX > 1260)
		dx = dt;
	if(mMouseY < 20)
		dy = -dt;
	if(mMouseY > 680)
		dy = dt;
	mCameraContral->moveCamera(dx,dy);
}

bool BattlePlayerState::keyPressed(const OIS::KeyEvent &arg)
{
	if (arg.key==OIS::KC_ESCAPE )
	{
		if (!mGUIMenu->getVisible())
		{
			mGUIMenu->setAllowSave(true);
			mGUIMenu->showScene("");
		}
		else
		{
			mGUIMenu->hideScene();
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

bool BattlePlayerState::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

void BattlePlayerState::createSelectPlane()
{
	Ogre::Entity* planeEnt=NULL;

	if (!Core::getSingletonPtr()->mSceneMgr->hasEntity("SelectSquadPlane"))
	{
		Ogre::Plane plane;
		plane.normal = Ogre::Vector3::UNIT_Y;
		plane.d = 0;

		Ogre::MeshManager::getSingleton().createPlane("Myplane",
			Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane,
			24,24,1,1,true,1,1,1,Ogre::Vector3::UNIT_Z);
		planeEnt=Core::getSingletonPtr()->mSceneMgr->createEntity( "SelectSquadPlane", "Myplane" );

		planeEnt->setMaterialName("SelectSquadPlane");
		planeNode=Core::getSingletonPtr()->mSceneMgr->getRootSceneNode()->createChildSceneNode("SelectSquadPlaneNode");

		planeNode->attachObject(planeEnt);
		planeNode->setVisible(false);
	}
	else
	{
		planeNode=Core::getSingletonPtr()->mSceneMgr->getSceneNode("SelectSquadPlaneNode");
		planeNode->setVisible(false);
	}
}

void BattlePlayerState::setSelectPlanePosition( int GX,int GY,float height )
{
	float wx,wy;
	Terrain::getSingletonPtr()->getWorldCoords(GX,GY,wx,wy);
	planeNode->setPosition(wx,height,wy);
	planeNode->setVisible(true);
}

void BattlePlayerState::setSelectPlanePosition( float height )
{
	int x,y;
	mSelectSquad->getCrood(&x,&y);
	setSelectPlanePosition(x,y,height);
}

void BattlePlayerState::hideSelectPlane()
{
	planeNode->setVisible(false);
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
		if (mMoveAreaGrap->inArea(GX,GY))
		{
			setSelectPlanePosition(GX,GY,SELECT_PLANE_HEIGHT_MOVE);
		}
		else
		{
			hideSelectPlane();
		}
		createPath(GX,GY);
		break;
	case PLAYERCONTROL_SKILL:
		Terrain::getSingleton().coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
		drawSkillTargetArea(GX,GY);
		if (mMoveAreaGrap->inArea(GX,GY))
		{
			setSelectPlanePosition(GX,GY,SELECT_PLANE_HEIGHT_MOVE);
		}
		else
		{
			hideSelectPlane();
		}	
		
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

						setSelectPlanePosition(SELECT_PLANE_HEIGHT);

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
					clearPathInfo(true);
					mState = PLAYERCONTROL_CHOOSESKILL;
				}
				else
				{
					executeMove(GX,GY);
				}
			}
			break;
		case PLAYERCONTROL_SKILL:
			useSkillAt(GX,GY);
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
				squadgrap->setDirection(d,true);
				mSquadWindow->setSquad(mSelectSquad);
			}
			break;
		case PLAYERCONTROL_MOVE:
			{
				setSelectPlanePosition(SELECT_PLANE_HEIGHT);

				mGUICommand->setSquad(mSelectSquad);
				clearPathInfo(true);
				mState = PLAYERCONTROL_CHOOSESKILL;
				break;
			}
		case PLAYERCONTROL_SKILL:
			{
				setSelectPlanePosition(SELECT_PLANE_HEIGHT);

				mGUICommand->setSquad(mSelectSquad);
				clearPathInfo(true);
				mSkillid = "none";
				mSkillType = SKILLTYPE_PASSIVE;
				mSkillArea = 0;
				mState = PLAYERCONTROL_CHOOSESKILL;
				break;
			}
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
	GUIInfoWindow* infoWindow=(GUIInfoWindow*)mGUIBattle->getSubWindow("InfoWindow");
	infoWindow->setCaption(StringTable::getSingletonPtr()->getString("PlayerTurn"),MyGUI::Colour::White);
	infoWindow->showScene("");
	for(int n = 0; n < mSquadManager->mSquadList.size(); n++)
	{
		if(mSquadManager->mSquadList[n]->getTeam() == 1)
		{
			mSquadManager->mSquadList[n]->newTurn();
			SquadGraphics* squadGrap=SquadGrapManager::getSingletonPtr()->getSquad(mSquadManager->mSquadList[n]->getGrapId());
			squadGrap->setSquadBillBoardState(true);
		}
	}
}

void BattlePlayerState::reactiveState()
{
	if(mSelectSquad->IsEliminated() == true)
	{
		mSquadWindow->setSquad(NULL);
		mGUICommand->setSquad(NULL);
		hideSelectPlane();
	}
	else if(mState == PLAYERCONTROL_MESSAGEBOX)
	{
		mSquadWindow->setSquad(mSelectSquad);
		if(mSelectSquad->getActionPoint() > 0.0f)
		{
			mGUICommand->setSquad(mSelectSquad);
		}
		mState = PLAYERCONTROL_CHOOSESKILL;

		if(mMessageBoxReturn == true)
		{
			if(mMoveTargetX != -1)
			{
				mGUICommand->setSquad(NULL);
				if(mTargetSquad != NULL)
					executeSkillOn(mMoveTargetX,mMoveTargetY, mTargetSquad);
				else
					executeMove(mMoveTargetX,mMoveTargetY);
			}
		}
		else
		{
			clearPathInfo(true);
			mMoveTargetX = -1;
			mMoveTargetY = -1;
			mTargetSquad = NULL;
		}
	}
	else
	{
		mSquadWindow->setSquad(mSelectSquad);
		setSelectPlanePosition(SELECT_PLANE_HEIGHT);
		if(mSelectSquad->getActionPoint() > 0.0f)
		{
			mGUICommand->setSquad(mSelectSquad);
		}
		else
		{
			SquadGraphics* squadGrap=SquadGrapManager::getSingletonPtr()->getSquad(mSelectSquad->getGrapId());
			squadGrap->setSquadBillBoardState(false);
		}
		mState = PLAYERCONTROL_CHOOSESKILL;

		mGUIState->setAllowNextTurn(true);
		if(mMoveTargetX != -1)
		{
			mMessageBoxReturn = false;
			mState = PLAYERCONTROL_MESSAGEBOX;
			mMainState->PushState(new BattleMessageBoxState(this,std::string("Test")));
		}
	}
	GUITargetWindows* targetwindow = static_cast<GUITargetWindows *>(mGUIBattle->getSubWindow("TargetWindow"));
	targetwindow->updateSquad();
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
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = East;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
 				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = East;
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
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = West;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = West;
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
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = South;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = South;
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
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = North;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = North;
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
		if(ite->second->mPrevApLeft >= apcost)
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

void BattlePlayerState::clearPathInfo(bool clearnode)
{
	if(clearnode)
	{	
		MapNodeIte movenodeite;
		for(movenodeite = mMoveMap.begin(); movenodeite != mMoveMap.end(); movenodeite++)
		{
			delete movenodeite->second;
		}
		mMoveMap.clear();
	}
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
	if(mTargetAreaGrap)
	{
		delete mTargetAreaGrap;
		mTargetAreaGrap = NULL;
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
				Direction d = ite->second->mDirectionToPrev;
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
	hideSelectPlane();
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
		Direction d = ite->second->mDirectionToPrev;
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
	int evt = 0;
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
	if(stoppoint != n && (evt & (MOVEEVENT_AMBUSH | MOVEEVENT_WRONG)) == 0 )
	{
		mMoveTargetX = x;
		mMoveTargetY = y;
		clearPathInfo(false);
	}
	else
	{
		mMoveTargetX = -1;
		mMoveTargetY = -1;
		clearPathInfo(true);
	}
	MoveCutScene* movecutscene = new MoveCutScene(mSelectSquad->getGrapId(),movepath,Ogre::Vector2(startx,starty));
	DirectionCutScene* dircutscene = new DirectionCutScene(mSelectSquad->getGrapId(),mSelectSquad->getDirection());
	BattleSquadManager::getSingleton().setCutScene(dircutscene);
	CutScene* eventcutscene = BattleSquadManager::getSingleton().getCutScene();
	movecutscene->setNextScene(eventcutscene);
	CutSceneDirector* cutscenedirector = new CutSceneDirector;
	cutscenedirector->addCutScene(movecutscene);
	mState = PLAYERCONTROL_CUTSCENE;
	mGUIState->setAllowNextTurn(false);
	mMainState->PushState(cutscenedirector);
}

void BattlePlayerState::useSkill(std::string skillid)
{
	DataLibrary* datalib = DataLibrary::getSingletonPtr();
	std::string skillpath = mSelectSquad->getPath() + std::string("/SkillTable/") + skillid;
	int cooldown;
	bool re = datalib->getData(skillpath + std::string("/CoolDown"),cooldown);
	if(!re || cooldown > 0)
		return;
	int aptype ;
	re = datalib->getData(std::string("StaticData/SkillData/")+ skillid+ std::string("/APType"),aptype);
	if(!re)
		return;
	float apcost;
	datalib->getData(std::string("StaticData/SkillData/")+ skillid+ std::string("/APCost"),apcost);
	float apleft = mSelectSquad->getActionPoint();
	if(aptype != SKILLAPTYPE_DEFENCE)
		apcost += mSelectSquad->getActionPointCost(aptype);
	else
		apcost = std::max(apcost,apleft);
	if(apleft < apcost)
		return;
	SkillType skilltype;
	datalib->getData(std::string("StaticData/SkillData/")+ skillid + std::string("/Type"),skilltype);
	if(skilltype == SKILLTYPE_PASSIVE)
		return;
	if(skilltype == SKILLTYPE_TARGETSELF)
	{
		CutScene* cutscene = BattleSquadManager::getSingleton().useSkillOn(mSelectSquad, mSelectSquad,skillid);
		if(cutscene!= NULL)
		{
			CutSceneDirector* cutscenedirector = new CutSceneDirector;
			cutscenedirector->addCutScene(cutscene);
			mState = PLAYERCONTROL_CUTSCENE;
			mGUIState->setAllowNextTurn(false);
			mMainState->PushState(cutscenedirector);
		}
		else
		{
			mSquadWindow->setSquad(mSelectSquad);
			if(mSelectSquad->getActionPoint() > 0.0f)
				mGUICommand->setSquad(mSelectSquad);
			else
				mGUICommand->setSquad(NULL);
		}
		return;
	}
	int minrange;
	int maxrange; 
	datalib->getData(std::string("StaticData/SkillData/")+ skillid + std::string("/MaxRange"),maxrange);
	datalib->getData(std::string("StaticData/SkillData/")+ skillid + std::string("/MinRange"),minrange);
	switch(skilltype)
	{
	case SKILLTYPE_TARGETENEMY:
	case SKILLTYPE_TARGETFRIEND:
	case SKILLTYPE_TARGETALL:
		if((minrange == 0 || minrange == 1)&& maxrange == 1)
		{
			drawSkillMoveArea(skilltype, apcost);
			mMeleeSkill = true;
		}
		else
		{
			drawSkillArea(skilltype,minrange,maxrange);
			mMeleeSkill = false;
		}
		break;
	case SKILLTYPE_TARGETAREA:
	case SKILLTYPE_TARGETLINE:
		drawSkillArea(skilltype,minrange,maxrange);
		mMeleeSkill = false;
		break;
	case SKILLTYPE_RANGED:
		std::string path = mSelectSquad->getPath();
		std::string sweaponid("none");
		datalib->getData(str(boost::format("%1%/SweaponId")%path),sweaponid);
		if(sweaponid == "none")
			return;
		int maxrangew = 0,minrangew = 0;
		path = str(boost::format("StaticData/SweaponData/%1%/")%sweaponid);
		datalib->getData(path + std::string("MaxRange"),maxrangew);
		datalib->getData(path + std::string("MinRange"),minrangew);
		maxrange += maxrangew;
		minrange += minrangew;
		drawSkillArea(skilltype,minrange,maxrange);
		break;
	}
	mGUICommand->setSquad(NULL);
	mSkillType = skilltype;
	mSkillid =skillid;
	mState = PLAYERCONTROL_SKILL;
}

void BattlePlayerState::drawSkillMoveArea(SkillType skilltype, float skillcost)
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
			int passable = skillPass(xx,yy, apcost, skilltype, skillcost);
			if(passable > 0 )
			{
				if(passable == 1)
				{
					coordlist.push_back(xx);
					coordlist.push_back(yy);
				}
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = East;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = East;
				}
			}
			xx = x + 1;
			yy = y;
			apcost = apleft;
			passable = skillPass(xx,yy, apcost, skilltype, skillcost);
			if(passable > 0 )
			{
				if(passable == 1)
				{
					coordlist.push_back(xx);
					coordlist.push_back(yy);
				}
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = West;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = West;
				}
			}
			xx = x;
			yy = y - 1;
			apcost = apleft;
			passable = skillPass(xx,yy, apcost, skilltype, skillcost);
			if(passable > 0 )
			{
				if(passable == 1)
				{
					coordlist.push_back(xx);
					coordlist.push_back(yy);
				}
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = South;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = South;
				}
			}
			xx = x;
			yy = y + 1;
			apcost = apleft;
			passable = skillPass(xx,yy, apcost, skilltype, skillcost);
			if(passable > 0 )
			{
				if(passable == 1)
				{
					coordlist.push_back(xx);
					coordlist.push_back(yy);
				}
				MapNodeIte ite;
				ite = mMoveMap.find(xx + yy * mapsize);
				if(ite == mMoveMap.end())
				{
					MoveNode* node = new MoveNode;
					node->x = xx;
					node->y = yy;
					node->mPrevApLeft = apleft;
					node->mAPleft = apleft - apcost;
					node->mDirectionToPrev = North;
					mMoveMap.insert(MapNodeType(xx + yy * mapsize, node));
				}
				else
				{
					ite->second->mPrevApLeft = apleft;
					ite->second->mAPleft = apleft - apcost;
					ite->second->mDirectionToPrev = North;
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
}

void BattlePlayerState::drawSkillArea(SkillType skilltype, int minrange, int maxrange)
{
	int x,y;
	mSelectSquad->getCrood(&x,&y);
	MapDataManager* mapdata = MapDataManager::getSingletonPtr();
	BattleSquadManager* battlesquadmanager = BattleSquadManager::getSingletonPtr();
	std::vector<int> skillcoordlist;
	for( int xx = x - maxrange; xx <= x + maxrange; xx++ )
	{
		for( int yy = y - maxrange; yy <= y + maxrange; yy++)
		{
			int irange = abs(xx - x) + abs(yy - y);
			if(irange <=  maxrange && irange >= minrange)
			{
				if(skilltype == SKILLTYPE_TARGETLINE)
				{
					if(xx == x && abs(yy - y) > 1)
						continue;
					if(yy == y && abs(xx - x) > 1)
						continue;
				}
				if(!mapdata->getPassable(xx,yy,0))
					continue;
				BattleSquad* blocksquad = battlesquadmanager->getBattleSquadAt(xx,yy,1,true);
				if(blocksquad == NULL)
				{
					skillcoordlist.push_back(xx);
					skillcoordlist.push_back(yy);
				}
				else
				{
					int team = blocksquad->getTeam();
					int relaction = blocksquad->getTeamFaction(team);
					switch(skilltype)
					{
					case SKILLTYPE_RANGED:
					case SKILLTYPE_TARGETENEMY:
						if(relaction > 0)
						{
							skillcoordlist.push_back(xx);
							skillcoordlist.push_back(yy);
						}
						break;
					case SKILLTYPE_TARGETFRIEND:
						if(relaction == 0)
						{
							skillcoordlist.push_back(xx);
							skillcoordlist.push_back(yy);
						}
						break;
					default:
						skillcoordlist.push_back(xx);
						skillcoordlist.push_back(yy);
						break;
					}
				}
			}
		}
	}
	mMoveAreaGrap = new AreaGrap(skillcoordlist,"CUBE_BLUE");
}

int BattlePlayerState::skillPass(int x, int y, float &apcost, SkillType skilltype, float skillcost)
{
	float apleft = apcost;
	bool passable = canPass(x,y,apcost);
	if(passable)
		return 1;
	int mapsize = MapDataManager::getSingleton().getMapSize();
	MapNodeIte ite;
	ite = mMoveMap.find(x + y * mapsize);
	if(ite != mMoveMap.end())
	{
		if(ite->second->mPrevApLeft >= apcost)
			return 0;
	}
	BattleSquad* blocksquad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,1,true);
	if(blocksquad == NULL || apleft < skillcost)
		return 0;
	int team = blocksquad->getTeam();
	int relaction = blocksquad->getTeamFaction(team);
	apcost = skillcost;
	switch(skilltype)
	{
	case SKILLTYPE_TARGETALL:
		return 2;
		break;
	case SKILLTYPE_TARGETENEMY:
		if(relaction > 0)
			return 2;
		return 0;
		break;
	case SKILLTYPE_TARGETFRIEND:
		if(relaction == 0)
			return 2;
		return 0;
		break;
	default:
		return 0;
		break;
	}
}

void BattlePlayerState::useSkillAt(int x,int y)
{
	if(!mMoveAreaGrap->inArea(x,y))
		return;
	BattleSquad* squad =NULL;
	switch(mSkillType)
	{
	case SKILLTYPE_TARGETSELF:
		executeSkillAt(x,y);
		break;
	case SKILLTYPE_TARGETALL:
		squad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,1,true);
		if(squad == NULL)
			return;
		if(mMeleeSkill)
			executeSkillOn( x,  y, squad);
		else
			executeSkillAt(x,y);
		break;
	case SKILLTYPE_TARGETENEMY:
		squad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,1,true);
		if(squad == NULL)
			return;
		if(squad->getTeamFaction(squad->getTeam()) > 0)
		{
			if(mMeleeSkill)
				executeSkillOn( x,  y, squad);
			else
				executeSkillAt(x,y);
		}
		break;
	case SKILLTYPE_TARGETFRIEND:
		squad = BattleSquadManager::getSingleton().getBattleSquadAt(x,y,1,true);
		if(squad == NULL)
			return;
		if(squad->getTeamFaction(squad->getTeam()) == 0)
		{
			if(mMeleeSkill)
				executeSkillOn( x,  y, squad);
			else
				executeSkillAt(x,y);
		}
		break;
	default:
		executeSkillAt(x, y);
		break;
	}
}

void BattlePlayerState::drawSkillTargetArea(int x,int y)
{
	if(mSkillType == SKILLTYPE_TARGETALL || mSkillType == SKILLTYPE_TARGETENEMY || mSkillType == SKILLTYPE_TARGETFRIEND)
	{
		if(mMeleeSkill)
			createPath(x,y);
	}
}

void BattlePlayerState::executeSkillAt(int x, int y)
{
	CutScene* battlecutscene = NULL;
	if(mSkillType == SKILLTYPE_TARGETLINE || mSkillType == SKILLTYPE_TARGETAREA)
	{
		battlecutscene = BattleSquadManager::getSingleton().useSkillAt(mSelectSquad,x,y, mSkillid);
		mSkillid = "none";
		mSkillType = SKILLTYPE_PASSIVE;
		clearPathInfo(true);
	}
	else
	{
		BattleSquad* battlesquad = BattleSquadManager::getSingleton().getBattleSquadAt(x ,y,1,true);
		if(battlesquad)
		{
			battlecutscene = BattleSquadManager::getSingleton().useSkillOn(mSelectSquad,battlesquad, mSkillid);
			mSkillid = "none";
			mSkillType = SKILLTYPE_PASSIVE;
			clearPathInfo(true);
		}
		else
			return;
	}
	if(battlecutscene != NULL)
	{
		CutSceneDirector* cutscenedirector = new CutSceneDirector;
		cutscenedirector->addCutScene(battlecutscene);
		mState = PLAYERCONTROL_CUTSCENE;
		mGUIState->setAllowNextTurn(false);
		mMainState->PushState(cutscenedirector);
	}
	else
	{
		mSquadWindow->setSquad(mSelectSquad);
		if(mSelectSquad->getActionPoint() > 0.0f)
		{
			mGUICommand->setSquad(mSelectSquad);
		}
		mState = PLAYERCONTROL_CHOOSESKILL;
	}
}

void BattlePlayerState::executeSkillOn(int x, int y, BattleSquad* squad)
{
	hideSelectPlane();
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
		Direction d = ite->second->mDirectionToPrev;
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
	while(croodlistrev.size()>2)
	{
		yyy = croodlistrev.back();
		croodlistrev.pop_back();
		xxx = croodlistrev.back();
		croodlistrev.pop_back();
		croodlist.push_back(xxx);
		croodlist.push_back(yyy);
	}
	int stoppoint;
	int evt = 0;
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
	if(stoppoint != n && (evt & (MOVEEVENT_AMBUSH | MOVEEVENT_WRONG)) == 0 )
	{
		mMoveTargetX = x;
		mMoveTargetY = y;
		mTargetSquad = squad;
		clearPathInfo(false);
	}
	else
	{
		mMoveTargetX = -1;
		mMoveTargetY = -1;
		mTargetSquad = NULL;
		clearPathInfo(true);
	}
	MoveCutScene* movecutscene = new MoveCutScene(mSelectSquad->getGrapId(),movepath,Ogre::Vector2(startx,starty));
	DirectionCutScene* dircutscene = new DirectionCutScene(mSelectSquad->getGrapId(),mSelectSquad->getDirection());
	BattleSquadManager::getSingleton().setCutScene(dircutscene);
	CutScene* evetcutscene = BattleSquadManager::getSingleton().getCutScene();
	movecutscene->setNextScene(evetcutscene);

	if(stoppoint == n)
	{
		CutScene* battlecutscene = BattleSquadManager::getSingleton().useSkillOn(mSelectSquad,squad,mSkillid);
		dircutscene->setNextScene(battlecutscene);
		mTargetSquad = NULL;
		mSkillid = "none";
		mSkillType = SKILLTYPE_PASSIVE;
	}
	CutSceneDirector* cutscenedirector = new CutSceneDirector;
	cutscenedirector->addCutScene(movecutscene);
	mState = PLAYERCONTROL_CUTSCENE;
	mGUIState->setAllowNextTurn(false);
	mMainState->PushState(cutscenedirector);
}
