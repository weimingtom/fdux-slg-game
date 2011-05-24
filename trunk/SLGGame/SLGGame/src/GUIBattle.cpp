#include "GUIBattle.h"

#include "GUIGameStateWindows.h"
#include "GUITerrainWindows.h"
#include "GUISquadWindows.h"
#include "GUIDeployWindow.h"
#include "GUICommandWindows.h"
#include "GUIMenuWindow.h"
#include "GUITargetWindow.h"

#include "Terrain.h"

#include "CollisionTools.h"
#include "CameraContral.h"

GUIBattle::GUIBattle(int Width,int Height):GUIScene("Battle.layout",Width,Height)
{
	MyGUI::Window* window;

	assignWidget(window,"Menu");
	mSubWindows.push_back(new GUIMenuWindow(window,Width,Height));
	assignWidget(window,"Terrain");
	mSubWindows.push_back(new GUITerrainWindows(window,Width,Height));
	assignWidget(window,"TargetWindow");
	mSubWindows.push_back(new GUITargetWindows(window,Width,Height));
	assignWidget(window,"SquadWindow");
	mSubWindows.push_back(new GUISquadWindows(window,Width,Height));
	assignWidget(window,"CommandWindow");
	mSubWindows.push_back(new GUICommandWindows(window,Width,Height));
	assignWidget(window,"GameState");
	mSubWindows.push_back(new GUIGameStateWindows(window,Width,Height));
	assignWidget(window,"DeployWindow");
	mSubWindows.push_back(new GUIDeployWindows(window,Width,Height));
	//assignWidget(mButton,"ShadowMapTarget");
}

GUIBattle::~GUIBattle(void)
{
}

void GUIBattle::showScene( std::string arg )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->showScene("");
	}
}

void GUIBattle::hideScene()
{

}

void GUIBattle::FrameEvent()
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->FrameEvent();
	}
}

void GUIBattle::SceneInputEvent( float x,float y )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if (!(*it)->SceneInputEvent(x,y))
		{
			break;
		}
	}

	int GX,GY;
	if(Terrain::getSingletonPtr()->coordinateToGrid(x,y,GX,GY))
	{
		GridInputEvent(GX,GY);
		//std::cout<<GX<<","<<GY<<std::endl;
	}
	/*
	MOC::CollisionTools collisontool(Core::getSingleton().mSceneMgr);
	Ogre::Vector2 mRenderWindowSize(Core::getSingletonPtr()->mWindow->getWidth(),Core::getSingletonPtr()->mWindow->getHeight());
	// 检查边界条件
	if  (x < 0 || x > mRenderWindowSize.x || y < 0 || y > mRenderWindowSize.y)
		return;

	//执行射线运算,获取与网格的交点
	Ogre::Ray ray = Core::getSingletonPtr()->mCamera->getCameraToViewportRay(x / mRenderWindowSize.x, y / mRenderWindowSize.y);

	Ogre::Vector3 point;
	Ogre::ulong target;
	float d;
	if(collisontool.raycast(ray,point,target,d,TERRAIN_MASK))
	{
		Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(
			0.5,    0,    0,  0.5, 
			0,   -0.5,    0,  0.5, 
			0,      0,    1,    0,
			0,      0,    0,    1);

		Ogre::Vector4 vector4(point.x,point.y,point.z,1);
		Ogre::Matrix4 cameraview= CameraContral::getSingleton().getShadowMapCamera()->getViewMatrix();
		Ogre::Matrix4 cameraproj= CameraContral::getSingleton().getShadowMapCamera()->getProjectionMatrixWithRSDepth();
		cameraview = PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * cameraproj * cameraview;
		vector4 = cameraview * vector4;
		//vector4 = vector4 * cameraproj;
		vector4.x /= vector4.w;
		vector4.y /= vector4.w;
		mButton->setPosition(vector4.x * 512 + 5,vector4.y * 512 + 5);
	}
	*/
}

void GUIBattle::GridInputEvent( int x,int y )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if ((*it)->GridInputEvent(x,y))
		{
			break;
		}
	}
}

GUISubWindows* GUIBattle::getSubWindow(std::string arg)
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if(arg == (*it)->getName())
			return (*it);
	}
	return NULL;
}

void GUIBattle::setBattleState( BattleState* state )
{
	mBattleState=state;

	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		(*it)->setBattleState(mBattleState);
	}
}

void GUIBattle::KeyInputEvent( const OIS::KeyEvent &arg )
{
	std::list<GUISubWindows*>::iterator it;
	for (it=mSubWindows.begin();it!=mSubWindows.end();it++)
	{
		if (!(*it)->KeyInputEvent(arg))
		{
			break;
		}
	}
}
