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

BattleDeployState::BattleDeployState(BattleState* mainState)
:SubBattleState(mainState)
{
	mCameraContral = new CameraContral;
	mCameraContral->resetCamera();
	mCameraContral->riseCameraTo(50.0f);
	Core::getSingleton().mInputControl->pushListener(this);
	mMouseX = 640;
	mMouseY = 320;
	//Core::getSingleton().mInputControl->setCameraContral(mCameraContral);

	//DataLibrary::getSingletonPtr()->loadXmlData(DataLibrary::GameData,"../media/mesh/sinbad.xml",true);
	//mSquadGrapManager=new SquadGrapManager(Core::getSingletonPtr()->mSceneMgr);
	//SquadGraphics* s;//=mSquadGrapManager->createSquad("SinbadSquad",1,10,10,SquadGrapManager::North,SquadGrapManager::Loose);
	//GUIPUDebug* puDebug=(GUIPUDebug*)GUISystem::getSingletonPtr()->createScene(PUDebugScene);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/Ture",1);
	DataLibrary::getSingletonPtr()->setData("GameData/BattleData/BattleState/CurTeam",1);
	mGUIBattle=(GUIBattle*)GUISystem::getSingletonPtr()->createScene(BattleScene);
	mGUIBattle->showScene("DeployWindow");
	mGUIBattle->setBattleState(mMainState);
	mDeployWindow = (GUIDeployWindows*)(mGUIBattle->getSubWindow("DeployWindow"));
	mDeployWindow->setDeployState(this);
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
	Core::getSingleton().mInputControl->popListener();
	delete mCameraContral;
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
	return true;
}
bool BattleDeployState::mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id)
{
	mGUIBattle->SceneInputEvent(arg.state.X.abs,arg.state.Y.abs);
	int GX,GY;
	Terrain::getSingletonPtr()->coordinateToGrid(arg.state.X.abs,arg.state.Y.abs,GX,GY);
	if(mSelectSquad)
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
		BattleControlState* controlstate = new BattleControlState(mMainState);
		mMainState->ChangeState(controlstate);
	}
}

void BattleDeployState::selectIndex(int index)
{
	mSelectSquad = mSquadManager->mDeployList[index];
	mSelectIndex = index;
}