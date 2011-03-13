#include "CameraContral.h"

#include "Terrain.h"

CameraContral::CameraContral(Terrain *terrain)
{
	mTerrain = terrain;
	mCamera = Core::getSingleton().mCamera;
}

CameraContral::~CameraContral()
{

}

void CameraContral::moveCamera(float dx,float dy)
{
	mX += dx;
	mY += dy;
	setCamera();
}

void ::CameraContral::riseCamera(float dh)
{
	mHeight += dh;
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
	float d = mHeight;//´ý¶¨¹«Ê½
	mCamera->setPosition(mX + d, height, mY +d);
	mCamera->lookAt(mX,mTerrain->getHeight(mX,mY), mY );
}