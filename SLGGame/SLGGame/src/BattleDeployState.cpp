#include "BattleDeployState.h"

#include "BattleState.h"
#include "CameraContral.h"
#include "Core.h"
#include "InputControl.h"
#include "SquadGrapManager.h"
#include "SquadGraphics.h"
#include "BattleSquadManager.h"
#include "BattleSquad.h"
#include "DataLibrary.h"
#include "Terrain.h"
#include "GUIPUDebug.h"
#include "GUIBattle.h"
#include "BattleControlState.h"
#include "GUIDeployWindow.h"
#include "AreaGrap.h"
#include "MapDataManager.h"
#include "GUISquadWindows.h"

BattleDeployState::BattleDeployState()
{
	mCameraContral = CameraContral::getSingletonPtr();
	mCameraContral->resetCamera();
	Core::getSingleton().mInputControl->pushListener(this);
	mMouseX = 640;
	mMouseY = 320;
	//Core::getSingleton().mInputControl->setCameraContral(mCameraContral);

	//DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml",true);
	//mSquadGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
	//SquadGraphics* s;//=mSquadGrapManager->createSquad("SinbadSquad",1,10,10,SquadGrapManager::North,SquadGrapManager::Loose);
	//GUIPUDebug* puDebug=(GUIPUDebug*)GUISystem::getSingletonPtr()->createScene(PUDebugScene);
	mGUIBattle=static_cast<GUIBattle *>(GUISystem::getSingletonPtr()->createScene(BattleScene));
	//mGUIBattle->setBattleState(mMainState);
	mDeployWindow = static_cast<GUIDeployWindows *>(mGUIBattle->getSubWindow("DeployWindow"));
	mDeployWindow->showScene("");
	mDeployWindow->setDeployState(this);
	mSquadWindow = static_cast<GUISquadWindows *>(mGUIBattle->getSubWindow("SquadWindow"));
	mSquadWindow->setSquad(NULL);
	mSquadManager = BattleSquadManager::getSingletonPtr();
	mSelectSquad = NULL;
	//建立部署小队列表
	BattleSquadManager::BattleSquadIte ite;
	std::vector<std::string> squadlist;
	for(ite = mSquadManager->mDeployList.begin(); ite != mSquadManager->mDeployList.end(); ite++)
	{
		squadlist.push_back((*ite)->getSquadName());
	}
	mDeployWindow->initList(squadlist);

	mAreaGrap = new AreaGrap(std::string("GameData/BattleData/MapData/Area/DeployArea/CoordList"),"CUBE_BLUE");

	//int k=1;
	//for (int i=8;i<14;i++)
	//{
	//	for (int j=8;j<13;j++)
	//	{
	//		s=mSquadGrapManager->createSquad("SinbadSquad",k,i,j,SquadGrapManager::North,SquadGrapManager::Loose);
	//		k++;
	//	}
	//}

}
BattleDeployState::~BattleDeployState()
{
	mDeployWindow->hideScene();
	mSquadWindow->setSquad(NULL);
	Core::getSingleton().mInputControl->popListener();
	delete mAreaGrap;
}

void BattleDeployState::update(unsigned int deltaTime)
{
	//mSquadGrapManager->update(deltaTime);

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

bool BattleDeployState::keyPressed(const OIS::KeyEvent &arg)
{
	//mGUIBattle->KeyInputEvent(arg);
	return false;
}
bool BattleDeployState::keyReleased(const OIS::KeyEvent &arg)
{
	return false;
}

bool BattleDeployState::mouseMoved(const OIS::MouseEvent &arg)
{
	mMouseX = arg.state.X.abs;
	mMouseY = arg.state.Y.abs;
	mGUIBattle->SceneInputEvent(arg.state.X.abs,arg.state.Y.abs);
	return true;
}
bool BattleDeployState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	int GX,GY;
	Terrain::getSingletonPtr()->coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
	if(mSelectSquad)
	{
		if(id == OIS::MB_Left)
		{
			MapDataManager* datamanager = MapDataManager::getSingletonPtr();
			if(mAreaGrap->inArea(GX,GY) && datamanager->getPassable(GX,GY,1))
			{
				int id = mSelectSquad->getGrapId();
				SquadGraphics* squadgrap = SquadGrapManager::getSingleton().getSquad(id);
				squadgrap->setGrid(GX,GY);
				mSelectSquad->setCrood(GX,GY);
				char info[64];
				sprintf_s(info,64,"%d,%d",GX,GY);
				mDeployWindow->setDeployInfo(mSelectIndex,std::string(info));
				if(mSquadManager->allDeployed())
					mDeployWindow->setAllowConfirm(true);
			}
		}
		else if(id == OIS::MB_Right)
		{
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
		}

	}
	return true;
}
bool BattleDeployState::mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	return false;
}

void BattleDeployState::deployConfirm()
{
	if(mSquadManager->allDeployed())
	{
		mSquadManager->deployConfirm();
		BattleControlState* controlstate = new BattleControlState(true);
		mMainState->ChangeState(controlstate);
	}
}

void BattleDeployState::selectIndex(int index)
{
	mSelectSquad = mSquadManager->mDeployList[index];
	mSquadWindow->setSquad(mSelectSquad);
	mSelectIndex = index;
}