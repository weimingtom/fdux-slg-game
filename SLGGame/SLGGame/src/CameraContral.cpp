#include "CameraContral.h"

#include "Terrain.h"

#include <iostream>

CameraContral::CameraContral()
{
	mTerrain = Terrain::getSingletonPtr();
	mCamera = Core::getSingleton().mCamera;
}

CameraContral::~CameraContral()
{

}

void CameraContral::moveCamera(float dx,float dy)
{
	mX +=  dx * 0.5 + dy * 0.5; //公式有误
	mY +=  dx * 0.5 - dy * 0.5; //公式有误
	setCamera();
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
	mHeight = 20.0f;
	setCamera();
}

void CameraContral::setCamera()
{
	float height = mHeight + mTerrain->getHeight(mX,mY);
	float d = mHeight;//待定公式
	mCamera->setPosition(mX + d, height, mY +d);
	mCamera->lookAt(mX,mTerrain->getHeight(mX,mY), mY );
}

void CameraContral::cameraQuery( int dx,int dy )
{
	Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(float(dx)/float(Core::getSingletonPtr()->mWindow->getWidth()),float(dy)/float(Core::getSingletonPtr()->mWindow->getHeight()));
	Ogre::RaySceneQuery* rsq=Core::getSingletonPtr()->mSceneMgr->createRayQuery(mouseRay);
	Ogre::RaySceneQueryResult r=rsq->execute();
	std::cout<<r.size()<<std::endl;

	std::cout<<mTerrain->getHeight(96,-144)<<std::endl;
}
