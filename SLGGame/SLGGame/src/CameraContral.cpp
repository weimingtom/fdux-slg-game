#include "CameraContral.h"

#include "Terrain.h"
#include "BillboardManager.h"
#include "SquadGrapManager.h"

//#define MAPCREATE

CameraContral::CameraContral()
{
	mTerrain = Terrain::getSingletonPtr();
	mCamera = Core::getSingleton().mCamera;
	mShadowMapCamera = Core::getSingleton().mSceneMgr->createCamera("ShadowMapCamera");
	mShadowMapCamera->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
	mShadowMapCamera->setOrthoWindow(136.0f,136.0f);
	mShadowMapCamera->setFarClipDistance(300.0f);
	mShadowMapCamera->setNearClipDistance(1.0f);
	Ogre::GpuSharedParametersPtr sharedparams = Ogre::GpuProgramManager::getSingleton().getSharedParameters("ShadowSharedParamsName");
	Ogre::Matrix4 PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE(
		0.5,    0,    0,  0.5, 
		0,   -0.5,    0,  0.5, 
		0,      0,    1,    0,
		0,      0,    0,    1);
	Ogre::Matrix4 cameraproj= PROJECTIONCLIPSPACE2DTOIMAGESPACE_PERSPECTIVE * mShadowMapCamera->getProjectionMatrixWithRSDepth();
	sharedparams->setNamedConstant("texProj",cameraproj);
	mMinX = 0.0f;
	mMinY = 0.0f;
	mTranslateVector=Ogre::Vector3::ZERO;
}

CameraContral::~CameraContral()
{

}

void CameraContral::setMoveRect(float minx, float miny)
{
	mMinX = minx;
	mMinY = miny;
}

void CameraContral::moveCamera(float dx,float dy)
{
#ifdef MAPCREATE
	 mCamera->setPosition(mCamera->getPosition()+(mCamera->getOrientation()*mTranslateVector));
	 if (dx==1)
	 {
		 mCamera->yaw(Ogre::Radian(mDx));
		 mCamera->pitch(Ogre::Radian(mDy));
	 }
#else
	mX +=  dx * 0.5f + dy * 0.5f;
	mY +=  -dx * 0.5f + dy * 0.5f;
	mX = (mX > -mMinX)? -mMinX: mX;
	mX = (mX < mMinX)? mMinX: mX;
	mY = (mY > -mMinY)? -mMinY: mY;
	mY = (mY < mMinY)? mMinY: mY;
	setCamera();
#endif
}

void ::CameraContral::riseCamera(float dh)
{
	mHeight += dh;
	mHeight = (mHeight > 100.0f)? 100.0f: mHeight;
	mHeight = (mHeight < 10.0f)? 10.0f: mHeight;
	setCamera();
}


void CameraContral::moveCameraTo(float x,float y)
{
	mX = x;
	mY = y;
	mX = (mX > -mMinX)? -mMinX: mX;
	mX = (mX < mMinX)? mMinX: mX;
	mY = (mY > -mMinY)? -mMinY: mY;
	mY = (mY < mMinY)? mMinY: mY;
	setCamera();
}

void ::CameraContral::riseCameraTo(float h)
{
	mHeight = h;
	mHeight = (mHeight > 100.0f)? 100.0f: mHeight;
	mHeight = (mHeight < 10.0f)? 10.0f: mHeight;
	setCamera();
}

void CameraContral::resetCamera()
{
	mX = 0.0f;
	mY = 0.0f;
	mHeight = 75.0f;
	setCamera();
}

void CameraContral::setCamera()
{
	//float height =mTerrain->getHeight(mX,mY);
	float d = 0.6 * mHeight;//´ý¶¨¹«Ê½
	mCamera->setPosition(mX + d,mHeight, mY +d);
	mCamera->lookAt(mX,0, mY );
	mShadowMapCamera->setPosition(mX - 98.0f, 80.0f, mY + 62.0f);
	mShadowMapCamera->lookAt(mX - 18.0f, 0.0f, mY - 18.0f );
}

void CameraContral::print()
{
	std::cout<<"D:"<<mCamera->getDirection().x<<","<<mCamera->getDirection().y<<","<<mCamera->getDirection().z<<std::endl;
	std::cout<<"O:"<<mCamera->getOrientation().x<<","<<mCamera->getOrientation().y<<","<<mCamera->getOrientation().z<<","<<mCamera->getOrientation().w<<std::endl;
	std::cout<<"P:"<<mCamera->getPosition().x<<","<<mCamera->getPosition().y<<","<<mCamera->getPosition().z<<std::endl;

	mCamera->setOrientation(Ogre::Quaternion(0.701285,-0.712852,0.00189269,0.00192394));
	mCamera->setPosition(0,400,0);
	BillboardManager::getSingletonPtr()->hideBillBoard();
	SquadGrapManager::getSingletonPtr()->hideSquad();
}